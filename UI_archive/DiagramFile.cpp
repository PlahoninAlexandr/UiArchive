#include "DiagramFile.h"

template<typename T>
using auto_cleanup = unique_ptr<T, std::function<void(T*)>>;

void DiagramFile::DoDraw(HDC hdc, HWND hWnd, PAINTSTRUCT ps, RECT& r, HFONT hFont, int& number) {
    hdc = BeginPaint(hWnd, &ps);
    SelectObject(hdc, hFont);
    for (int i = number - 1; i >= 0; --i) {
        r.top = 250;
        r.left = lft;
        r.right = rht;
        r.bottom = height[i];

        wstring tmp_name(name[i].begin(), name[i].end());
        TextOut(hdc, rht, height[i] - 30, tmp_name.c_str(), tmp_name.size());

        string s = to_string(size[i]);
        wstring tmp2(s.begin(), s.end());
        TextOut(hdc, rht, 250, tmp2.c_str(), tmp2.size());

        FillRect(hdc, &r, HBRUSH(CreateSolidBrush(RGB(27, 58, 194))));
        lft += 80;
        rht += 80;
    }

    EndPaint(hWnd, &ps);
}

void DiagramFile::DoParameters(HWND hWnd, wstring str, string global_archive, int& number, HWND hWnd1, HWND hWnd2) {
    openArchive(hWnd);

    if (GetOpenFileName(&ofn) == TRUE) {
        str = ofn.lpstrFile;
        global_archive = string(str.begin(), str.end());

        amount_size_files = sizeFiles(global_archive, number);
        sort(amount_size_files.begin(), amount_size_files.end());

        for (auto arg : amount_size_files) {
            size.push_back(arg.first);
            name.push_back(arg.second);
        }

        auto it = size.begin();
        advance(it, size.size() - 1);
        max_size = *it;

        ratio(max_size, size, height);

        SetWindowPos(hWnd1, HWND_NOTOPMOST, 200, 200, 800, 350, NULL);
        EnableWindow(hWnd2, FALSE);
        UpdateWindow(hWnd1);
        ShowWindow(hWnd1, SW_SHOWNORMAL);
    }
}

vector<pair<float, string>> DiagramFile::sizeFiles(const string path, int& count) {
    struct archive_entry* entry;
    int r;
    float size;
    string text;
    vector <pair<float, string>> files;

    auto_cleanup<struct archive> a(archive_read_new(), [](struct archive* a) { archive_read_free(a); });
    archive_read_support_filter_all(&*a);
    archive_read_support_format_all(&*a);
    r = archive_read_open_filename(&*a, path.c_str(), 10240);
    if (r != ARCHIVE_OK)
        exit(1);
    while (archive_read_next_header(&*a, &entry) == ARCHIVE_OK) {
        text = archive_entry_pathname(entry);
        size = archive_entry_size(entry);
        size /= 1024;
        size /= 1024;
        files.push_back(make_pair(size, text));
        count++;
        archive_read_data_skip(&*a);
    }
    return files;
}

void DiagramFile::ratio(float max, vector<float> vec, vector<int>& hg) {
    vector<int>mnb;
    for (auto i : vec) {
        mnb.push_back(i / max * 100);
    }
    for (auto i : mnb) {
        hg.push_back(250 - (i * 2));
    }
    sort(hg.begin(), hg.end(), greater<>());
}

void DiagramFile::openArchive(HWND hWnd) {
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file;
    ofn.nMaxFile = sizeof(file);
    ofn.lpstrFilter = _T("zip\0*.zip*\0Text\0*.TXT\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}