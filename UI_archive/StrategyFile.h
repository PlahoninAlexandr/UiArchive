#pragma once

#include <ArchiveFunction.h>

class StrategyFile {
public:
    virtual ~StrategyFile() {}
    virtual void DoAlgorithm(WPARAM wParam) = 0;
};