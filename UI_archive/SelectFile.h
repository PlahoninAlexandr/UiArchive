#pragma once

#include "StrategyFile.h"
#include <ArchiveFunction.h>

class SelectFile : public StrategyFile {
public:
    void DoAlgorithm(WPARAM wParam, wstring str, string path, vector<string> argv, string outname) override;
};