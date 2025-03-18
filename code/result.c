#include "result.h"

Result err_new(const char *err_str) {
	Result result;
	result.err_ed = true;
	result.err_str = err_str;
	return result;
}

Result ok_new(void) {
	Result result;
	result.err_ed = false;
	result.err_str = "";
	return result;
}
