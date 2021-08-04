#pragma once

#include "StrategyDiagram.h"

class ContextDiagram {
    StrategyDiagram* strategy_;
    wstring str;
public:
    ContextDiagram(StrategyDiagram* strategy = nullptr);
    ~ContextDiagram();
    void set_strategy(StrategyDiagram* strategy);
    void draw(HDC hdc, HWND hWnd, PAINTSTRUCT ps, RECT& r, HFONT hFont, int& number);
    void setParameters(HWND hWnd, string global_archive, int& number, HWND hWnd1, HWND hWnd2);
};