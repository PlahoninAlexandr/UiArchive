#include "ContextFile.h"

ContextFile::ContextFile(StrategyFile* strategy) : strategy_(strategy) {}

ContextFile::~ContextFile(){ delete this->strategy_; }

void ContextFile::set_strategy(StrategyFile* strategy) {
	delete this->strategy_;
	this->strategy_ = strategy;
}

void ContextFile::dropLogic(WPARAM wParam) {
	this->strategy_->DoAlgorithm(wParam);
}