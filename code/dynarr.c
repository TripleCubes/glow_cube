#include "dynarr.h"

#include <string.h>
#include "maybe.h"

#define DYNARR_DEFINE(type, func_name, struct_name)\
Maybe dynarr_##func_name##_cap_new(Dynarr##struct_name *dynarr, size_t cap) {\
	dynarr->sz = 0;\
	dynarr->cap = cap;\
	dynarr->ptr = malloc(cap * sizeof(type));\
	if (dynarr->ptr == NULL) {\
		return ERR("dynarr_new(): malloc failed");\
	}\
	return OK;\
}\
\
Maybe dynarr_##func_name##_new(Dynarr##struct_name *dynarr) {\
	return dynarr_##func_name##_cap_new(dynarr, 2);\
}\
\
Maybe dynarr_##func_name##_push(Dynarr##struct_name *dynarr, type v) {\
	if (dynarr->sz == dynarr->cap) {\
		dynarr->ptr = realloc(dynarr->ptr, dynarr->cap * 2 *sizeof(type));\
		if (dynarr->ptr == NULL) {\
			return ERR("dynarr_push(): realloc failed");\
		}\
	}\
\
	dynarr->ptr[dynarr->sz] = v;\
	dynarr->sz++;\
	return OK;\
}\
\
type dynarr_##func_name##_pop(Dynarr##struct_name *dynarr) {\
	dynarr->sz--;\
	return dynarr->ptr[dynarr->sz];\
}\
\
Maybe dynarr_##func_name##_insert(Dynarr##struct_name *dynarr,\
const type *arr2, size_t arr2sz) {\
	size_t nx_sz = dynarr->sz + arr2sz;\
	if (nx_sz > dynarr->cap) {\
		size_t nx_cap = dynarr->cap;\
		while (nx_cap < nx_sz) {\
			nx_cap *= 2;\
		}\
\
		dynarr->ptr = realloc(dynarr->ptr, nx_cap * sizeof(type));\
		if (dynarr->ptr == NULL) {\
			return ERR("dynarr_insert(): realloc failed");\
		}\
	}\
\
	memcpy(dynarr->ptr + dynarr->sz, arr2, arr2sz * sizeof(type));\
	dynarr->sz = nx_sz;\
	return OK;\
}\
\
void  dynarr_##func_name##_clear(Dynarr##struct_name *dynarr) {\
	dynarr->sz = 0;\
}\
\
void dynarr_##func_name##_release(Dynarr##struct_name *dynarr) {\
	free(dynarr->ptr);\
}

DYNARR_DEFINE(int, int, Int)
DYNARR_DEFINE(char, char, Char)
