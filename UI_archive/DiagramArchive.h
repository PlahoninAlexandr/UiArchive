#pragma once

#include "StrategyDiagram.h"

class DiagramArchive : public StrategyDiagram {
	vector<pair<float, string>> amount_size_files;
	vector<float> size;
	vector<string> name;
	vector<int> height;
	float max_size, size_archive;
	int lft = 70, rht = 50;
	wchar_t file[1024];
	OPENFILENAME ofn;
	wstring str;

	vector<pair<float, string>>sizeFiles(const string path, int& count, float &sizeArch);
	void ratio(float max, vector<float> vec, vector<int>& hg);
	void openArchive(HWND hWnd);
	string lastWordFile(string word);
public:
	void DoDraw(HDC hdc, HWND hWnd, PAINTSTRUCT ps, RECT& r, HFONT hFont, int& number) override;
	void DoParameters(HWND hWnd, wstring str, string global_archive, int& number, HWND hWnd1, HWND hWnd2) override;
};