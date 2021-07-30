#include "DropFile.h"

template<typename T>
using auto_cleanup = unique_ptr<T, std::function<void(T*)>>;

string DropFile::lastWordDirectory(string word) {
    vector<string> vec;

    string myText = word;
    istringstream iss(myText);
    string token;
    while (getline(iss, token, '\\')) vec.push_back(token);

    if (vec[vec.size() - 3] != tmp_path) return vec[vec.size() - 3] + "\\" + vec[vec.size() - 2] + "\\" + vec[vec.size() - 1];
    else if (vec[vec.size() - 2] != tmp_path) return vec[vec.size() - 2] + "\\" + vec[vec.size() - 1];
    else return vec[vec.size() - 1];
}

string DropFile::lastWordFile(string word) {
    vector<string> vec;

    string myText = word;
    istringstream iss(myText);
    string token;
    while (getline(iss, token, '\\')) vec.push_back(token);

    return vec[vec.size() - 1];
}

void DropFile::DoAlgorithm(WPARAM wParam, HWND hWnd, wstring str, string path, vector<string> argv, string outname) {
    Flag = 0;
    size = MAX_PATH;
    p_filename = new wchar_t[size];
    DragQueryFile((HDROP)wParam, 0, p_filename, size);
    str = p_filename;
    path = tmp_path = string(str.begin(), str.end());
    argv.push_back(path);

    saveFile();

    if (GetSaveFileName(&ofn) == TRUE) {
        str = ofn.lpstrFile;
        outname = string(str.begin(), str.end());

        write_archive(outname, argv);
    }
    DragFinish((HDROP)wParam);
    delete p_filename;
}

void DropFile::saveFile() {
    char szDefExt[260];
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = file;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(file);
    ofn.lpstrFilter = L"(*.zip)\0*.zip\0";
    ofn.lpstrDefExt = (LPCWSTR)szDefExt;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}

void DropFile::write_archive(const string outname_tmp, const vector<string> filename) {
    string outname = lastWordFile(outname_tmp);
    struct stat st;
    int len;
    string ss;

    auto_cleanup<struct archive> a(archive_write_new(), [](struct archive* a) { archive_write_close(a); archive_write_free(a); });
    archive_write_set_format_zip(&*a);
    archive_write_set_format_pax_restricted(&*a);
    archive_write_open_filename(&*a, outname.c_str());
    tmp_path = lastWordFile(tmp_path);

    for (auto i : filename) {
        stat(i.c_str(), &st);
        auto_cleanup<struct archive_entry> entry(archive_entry_new(), [](struct archive_entry* entry) { archive_entry_free(entry); });
        if (Flag == 1) archive_entry_set_pathname(&*entry, lastWordDirectory(i).c_str());
        else archive_entry_set_pathname(&*entry, lastWordFile(i).c_str());
        archive_entry_set_size(&*entry, st.st_size);
        archive_entry_set_filetype(&*entry, AE_IFREG);
        archive_entry_set_perm(&*entry, 0644);
        archive_write_header(&*a, &*entry);
        auto_cleanup<FILE> pFile(fopen(i.c_str(), "rb"), [](FILE* pFile) { fclose(pFile); });
        fseek(&*pFile, 0, SEEK_END);
        size_t size = ftell(&*pFile);
        ss.resize(size);
        rewind(&*pFile);
        len = fread(&ss[0], 1, size, &*pFile);
        while (len > 0) {
            archive_write_data(&*a, &ss[0], len);
            len = fread(&ss[0], 1, size, &*pFile);
        }
        ss.clear();
    }
    readArchive(outname_tmp);
}

void DropFile::readArchive(const string path) {
    struct archive_entry* entry;
    int r;
    string text;

    auto_cleanup<struct archive> a(archive_read_new(), [](struct archive* a) { archive_read_free(a); });
    archive_read_support_filter_all(&*a);
    archive_read_support_format_all(&*a);
    r = archive_read_open_filename(&*a, path.c_str(), 10240);
    if (r != ARCHIVE_OK)
        exit(1);
    while (archive_read_next_header(&*a, &entry) == ARCHIVE_OK) {
        text += archive_entry_pathname(entry);
        text += "\n";
        archive_read_data_skip(&*a);
    }
    MessageBoxA(NULL, text.c_str(), "List", MB_ICONINFORMATION | MB_OKCANCEL);
}