#ifndef STR_HEADER
#define STR_HEADER

#include "dynarr.h"

typedef struct _Result Result;
typedef DynarrChar Str;

Result str_new(Str *str);
Result str_cap_new(Str *str, size_t cap);
Result str_from(Str *str, const char *str2);
Result str_push(Str *str, char c);
Result str_insert(Str *str, const char *str2);
Result str_set(Str *str, const char *str2);
void str_print(Str *str);
void str_println(Str *str);
void str_clear(Str *str);
void str_release(Str *str);

#endif
