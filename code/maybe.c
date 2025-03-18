#include "maybe.h"

Maybe err_new(const char *err_str) {
	Maybe maybe;
	maybe.err_ed = true;
	maybe.err_str = err_str;
	return maybe;
}

Maybe ok_new(void) {
	Maybe maybe;
	maybe.err_ed = false;
	maybe.err_str = "";
	return maybe;
}
