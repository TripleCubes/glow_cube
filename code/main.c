#include <stdio.h>
#include "maybe.h"
#include "str.h"

int main(void) {
	Str str;
	HANDLE_MAIN(str_from(&str, "this is a test"));
	HANDLE_MAIN(str_insert(&str, " 10"));
	str_println(&str);

	HANDLE_MAIN(str_set(&str, "hey now brown cow"));
	str_println(&str);

	str_release(&str);

	printf("reached end of main()\n");

	return 0;
}
