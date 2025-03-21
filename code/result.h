#ifndef RESULT_HEADER
#define RESULT_HEADER

#include <stdbool.h>
#include <stdio.h>

#define ERR(err_str) err_new(err_str)
#define OK ok_new()

#define HANDLE(x) {\
	Result r = x; if (r.err_ed) { return ERR(r.err_str); }\
}
#define HANDLE_MAIN(x) {\
	Result r = x; if (r.err_ed) { printf("%s\n", r.err_str); return 0; }\
}

struct _Result {
	bool err_ed;
	const char *err_str;
};
typedef struct _Result Result;

Result err_new(const char *err_str);
Result ok_new(void);

#endif
