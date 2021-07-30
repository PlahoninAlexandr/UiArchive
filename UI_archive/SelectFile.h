#pragma once

#include "StrategyFile.h"
#include <ArchiveFunction.h>

class SelectFile : public StrategyFile {
public:
    void DoAlgorithm(WPARAM wParam, HWND hWnd, wstring str, string path, vector<string> argv, string outname) override;
};