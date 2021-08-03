#pragma once

#include "StrategyFile.h"

class ContextFile {
    StrategyFile* strategy_;
public:
    ContextFile(StrategyFile* strategy = nullptr);
    ~ContextFile();
    void set_strategy(StrategyFile* strategy);
    void dropLogic(WPARAM wParam, wstring str, string path, vector<string> argv, string outname);
};