#ifndef DYNARR_HEADER
#define DYNARR_HEADER

#include <stdlib.h>

typedef struct _Maybe Maybe;

#define DYNARR_DECLARE(type, func_name, struct_name)\
struct _Dynarr##struct_name {\
	size_t sz;\
	size_t cap;\
	type *ptr;\
};\
typedef struct _Dynarr##struct_name Dynarr##struct_name;\
\
Maybe dynarr_##func_name##_cap_new(Dynarr##struct_name *dynarr, size_t cap);\
Maybe dynarr_##func_name##_new(Dynarr##struct_name *dynarr);\
Maybe dynarr_##func_name##_push(Dynarr##struct_name *dynarr, type v);\
type  dynarr_##func_name##_pop(Dynarr##struct_name *dynarr);\
Maybe dynarr_##func_name##_insert(Dynarr##struct_name *dynarr,\
	const type *arr2, size_t arr2sz);\
void  dynarr_##func_name##_clear(Dynarr##struct_name *dynarr);\
void  dynarr_##func_name##_release(Dynarr##struct_name *dynarr);\

DYNARR_DECLARE(int, int, Int)
DYNARR_DECLARE(char, char, Char)

#endif
