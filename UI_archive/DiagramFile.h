#pragma once

#include "StrategyDiagram.h"

class DiagramFile : public StrategyDiagram {
	vector<pair<float, string>> amount_size_files;
	vector<float> size;
	vector<string> name;
	vector<int> height;
	float max_size;
	int lft = 70, rht = 50;
	wchar_t file[1024];
	OPENFILENAME ofn;

	vector<pair<float, string>>sizeFiles(const string path, int& count);
	void ratio(float max, vector<float> vec, vector<int>& hg);
	void openArchive(HWND hWnd);
public:
    void DoDraw(HDC hdc, HWND hWnd, PAINTSTRUCT ps, RECT& r, HFONT hFont, int& number) override;
    void DoParameters(HWND hWnd, wstring str, string global_archive, int& number, HWND hWnd1, HWND hWnd2) override;
};