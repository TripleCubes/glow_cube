#include "file.h"

#include <stdio.h>
#include <stdbool.h>
#include "result.h"
#include "str.h"

Result file_read(Str *str, const char *path) {
	FILE *f = fopen(path, "r");
	if (f == NULL) {
		return ERR("file_read(): fopen() error");
	}

	while (true) {
		int c = getc(f);
		if (c == EOF) {
			break;
		}
		HANDLE(str_push(str, (char)c));
	}

	if (fclose(f) == EOF) {
		return ERR("file_read(): fclose() error");
	}
	return OK;
}
