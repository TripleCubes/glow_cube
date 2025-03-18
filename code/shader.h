#ifndef SHADER_HEADER
#define SHADER_HEADER

typedef struct _Result Result;

Result shader_new(unsigned int *shader_id, const char *v_path,
	const char *f_path);

#endif
