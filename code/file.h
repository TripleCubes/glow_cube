#ifndef FILE_HEADER
#define FILE_HEADER

typedef struct _Result Result;
typedef struct _DynarrChar Str;

Result file_read(Str *str, const char *path);

#endif
