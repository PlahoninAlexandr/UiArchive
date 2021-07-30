#include "ContextFile.h"

ContextFile::ContextFile(StrategyFile* strategy) : strategy_(strategy) {}

ContextFile::~ContextFile(){ delete this->strategy_; }

void ContextFile::set_strategy(StrategyFile* strategy) {
	delete this->strategy_;
	this->strategy_ = strategy;
}

void ContextFile::dropLogic(WPARAM wParam, HWND hWnd, wstring str, string path, vector<string> argv, string outname) {
	this->strategy_->DoAlgorithm(wParam, hWnd, str, path, argv, outname);
}