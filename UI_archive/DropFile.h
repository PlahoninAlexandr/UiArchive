#pragma once

#include "StrategyFile.h"

class DropFile : public StrategyFile {
    string tmp_path;
    int size, Flag;
    wchar_t* p_filename;
    wchar_t file[1024];
    OPENFILENAME ofn;
    wstring str;
    string path, outname;
    vector<string> argv;

    void saveFile();
    void write_archive(const string outname_tmp, const vector<string> filename);
    string lastWordFile(string word);
    void readArchive(const string path);
    string lastWordDirectory(string word);
public:
    void DoAlgorithm(WPARAM wParam) override;
};