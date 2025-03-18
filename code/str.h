#ifndef STR_HEADER
#define STR_HEADER

#include "dynarr.h"

typedef struct _Maybe Maybe;
typedef DynarrChar Str;

Maybe str_new(Str *str);
Maybe str_cap_new(Str *str, size_t cap);
Maybe str_from(Str *str, const char *str2);
Maybe str_insert(Str *str, const char *str2);
Maybe str_set(Str *str, const char *str2);
void str_print(Str *str);
void str_println(Str *str);
void str_clear(Str *str);
void str_release(Str *str);

#endif
