#include "SelectFile.h"

void SelectFile::DoAlgorithm(WPARAM wParam, wstring str, string path, vector<string> argv, string outname) {
	unique_ptr<ArchiveFunction> arch(new ArchiveFunction);
	arch->writeArchiveSingle(str, path, argv, outname);
}