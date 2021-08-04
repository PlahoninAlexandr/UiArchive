#pragma once

#include "StrategyFile.h"
#include <ArchiveFunction.h>

class SelectFile : public StrategyFile {
public:
    void DoAlgorithm(WPARAM wParam) override;
};