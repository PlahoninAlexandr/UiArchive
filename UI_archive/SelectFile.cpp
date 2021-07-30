#include "SelectFile.h"

void SelectFile::DoAlgorithm(WPARAM wParam, HWND hWnd, wstring str, string path, vector<string> argv, string outname) {
	unique_ptr<ArchiveFunction> arch(new ArchiveFunction);
	arch->writeArchiveSingle(hWnd, str, path, argv, outname);
}