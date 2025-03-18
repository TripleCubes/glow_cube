#include <stdio.h>
#include "result.h"
#include "str.h"
#include "file.h"

int main(void) {
	Str str;
	HANDLE_MAIN(str_cap_new(&str, 4096));

	HANDLE_MAIN(file_read(&str, "shader/main_v.glsl"));

	str_print(&str);
	str_release(&str);

	printf("reached end of main()\n");

	return 0;
}
