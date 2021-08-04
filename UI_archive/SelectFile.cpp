#include "SelectFile.h"

void SelectFile::DoAlgorithm(WPARAM wParam) {
	unique_ptr<ArchiveFunction> arch(new ArchiveFunction);
	arch->writeArchiveSingle();
}