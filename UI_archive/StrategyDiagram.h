#pragma once

#include <ArchiveFunction.h>

class StrategyDiagram {
public:
    virtual ~StrategyDiagram() {}
    virtual void DoDraw(HDC hdc, HWND hWnd, PAINTSTRUCT ps, RECT& r, HFONT hFont, int& number) = 0;
    virtual void DoParameters(HWND hWnd, wstring str, string global_archive, int& number, HWND hWnd1, HWND hWnd2) = 0;
};