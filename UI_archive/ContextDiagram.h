#pragma once

#include "StrategyDiagram.h"

class ContextDiagram {
    StrategyDiagram* strategy_;
public:
    ContextDiagram(StrategyDiagram* strategy = nullptr);
    ~ContextDiagram();
    void set_strategy(StrategyDiagram* strategy);
    void draw(HDC hdc, HWND hWnd, PAINTSTRUCT ps, RECT& r, HFONT hFont, int& number);
    void setParameters(HWND hWnd, wstring str, string global_archive, int& number, HWND hWnd1, HWND hWnd2);
};