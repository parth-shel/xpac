#include <stdio.h>
#include <libtar.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	TAR *pTar;
	if (argc == 4) {
		char *tarFilename = argv[1];
		char *srcDir = argv[2];

		char *extractTo = argv[3];

		tar_open(&pTar, tarFilename, NULL, O_WRONLY | O_CREAT, 0644, TAR_IGNORE_MAGIC);
		tar_append_tree(pTar, srcDir, extractTo);
		tar_append_eof(pTar);
		tar_close(pTar);
	}
	else {
		fprintf(stdout,"Usage : arg1 : file.tar \n arg2 : directory \n arg3 : extract to \n");
	}
	return (0);
}
