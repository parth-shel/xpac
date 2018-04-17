#include <stdio.h>
#include <libtar.h>
#include <fcntl.h>

#include "tar.h"

int tar(const char* path, const char* tar_path) {
	TAR *tar_file;
	char *tar_file_name = (char*) tar_path;
	char *src_dir = (char*) path;
	char *extract_to = (char*) path;
	if(tar_open(&tar_file, tar_file_name, NULL, O_WRONLY | O_CREAT, 0644, TAR_IGNORE_MAGIC) != 0) {
		return -1;
	}
	if(tar_append_tree(tar_file, src_dir, extract_to) != 0) {
		return -1;
	}
	if(tar_append_eof(tar_file) != 0) {
		return -1;
	}
	if(tar_close(tar_file) != 0) {
		return -1;
	}

	return 0;
}

int untar(const char* path, const char* untar_path) {
	TAR * tar_file;
	char* tar_file_name = (char*) path;
	char* extract_to = (char*) untar_path;
	if (tar_open(&tar_file, tar_file_name, NULL, O_RDONLY, 0, TAR_IGNORE_MAGIC) != 0) {
		return -1;
	}
	if (tar_extract_all(tar_file, extract_to) != 0) {
		return -1;
	}
	if (tar_close(tar_file) != 0) {
		return -1;
	}

	return 0;
}
