#pragma once

#include "StrategyFile.h"

class ContextFile {
    StrategyFile* strategy_;
    wstring str;
    string path, outname;
    vector<string> argv;
public:
    ContextFile(StrategyFile* strategy = nullptr);
    ~ContextFile();
    void set_strategy(StrategyFile* strategy);
    void dropLogic(WPARAM wParam);
};