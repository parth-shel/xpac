#include <stdio.h>
#include <libtar.h>
#include <fcntl.h>

#include "tar.h"

int tar(const char* path, const char* tar_path) {
	TAR *pTar;
	char *tarFilename = (char*) tar_path;
	char *srcDir = (char*) path;
	char *extractTo = (char*) path;
	tar_open(&pTar, tarFilename, NULL, O_WRONLY | O_CREAT, 0644, TAR_IGNORE_MAGIC);
	tar_append_tree(pTar, srcDir, extractTo);
	tar_append_eof(pTar);
	tar_close(pTar);

	return 0;
}

int untar(const char* path) {
	return 0;
}
