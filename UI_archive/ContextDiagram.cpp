#include "ContextDiagram.h"

ContextDiagram::ContextDiagram(StrategyDiagram* strategy) : strategy_(strategy) {}

ContextDiagram::~ContextDiagram() { delete this->strategy_; }

void ContextDiagram::set_strategy(StrategyDiagram* strategy) {
	delete this->strategy_;
	this->strategy_ = strategy;
}

void ContextDiagram::draw(HDC hdc, HWND hWnd, PAINTSTRUCT ps, RECT& r, HFONT hFont, int& number) {
	this->strategy_->DoDraw(hdc, hWnd, ps, r, hFont, number);
}

void ContextDiagram::setParameters(HWND hWnd, wstring str, string global_archive, int& number, HWND hWnd1, HWND hWnd2) {
	this->strategy_->DoParameters(hWnd, str, global_archive, number, hWnd1, hWnd2);
}