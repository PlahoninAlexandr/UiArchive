#pragma once

#include <ArchiveFunction.h>

class StrategyFile {
public:
    virtual ~StrategyFile() {}
    virtual void DoAlgorithm(WPARAM wParam, HWND hWnd, wstring str, string path, vector<string> argv, string outname) = 0;
};