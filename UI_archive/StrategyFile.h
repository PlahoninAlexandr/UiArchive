#pragma once

#include <ArchiveFunction.h>

class StrategyFile {
public:
    virtual ~StrategyFile() {}
    virtual void DoAlgorithm(WPARAM wParam, wstring str, string path, vector<string> argv, string outname) = 0;
};