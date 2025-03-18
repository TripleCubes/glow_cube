#include "str.h"

#include <stdio.h>
#include <string.h>
#include "result.h"

Result str_new(Str *str) {
	return dynarr_char_new(str);
}

Result str_cap_new(Str *str, size_t cap) {
	return dynarr_char_cap_new(str, cap);
}

Result str_from(Str *str, const char *str2) {
	HANDLE(dynarr_char_new(str));
	HANDLE(dynarr_char_insert(str, str2, strlen(str2)));
	return OK;
}

Result str_push(Str *str, char c) {
	return dynarr_char_push(str, c);
}

Result str_insert(Str *str, const char *str2) {
	return dynarr_char_insert(str, str2, strlen(str2));
}

Result str_set(Str *str, const char *str2) {
	dynarr_char_clear(str);
	HANDLE(dynarr_char_insert(str, str2, strlen(str2)));
	return OK;
}

void str_print(const Str *str) {
	printf("%.*s", (int)str->sz, str->ptr);
}

void str_println(const Str *str) {
	str_print(str);
	printf("\n");
}

Result c_str(char **out, const Str *str) {
	*out = malloc((str->sz + 1) * sizeof(char));
	if (*out == NULL) {
		return ERR("c_str(): malloc failed");
	}

	memcpy(*out, str->ptr, str->sz * sizeof(char));
	(*out)[str->sz] = '\0';

	return OK;
}

void str_clear(Str *str) {
	dynarr_char_clear(str);
}

void str_release(Str *str) {
	dynarr_char_release(str);
}
