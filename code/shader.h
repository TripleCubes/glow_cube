#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <stdbool.h>

typedef struct _Result Result;
typedef struct _Mat4 Mat4;
typedef struct _Vec3 Vec3;

Result shader_new(unsigned int *shader_id, const char *v_path,
	const char *f_path);

void shader_u_mat4(unsigned int shader_id, const char *uniform, const Mat4 *m);
void shader_u_vec3(unsigned int shader_id, const char *uniform, const Vec3 v);
void shader_u_2f(unsigned int shader_id, const char *uniform, float a, float b);
void shader_u_bool(unsigned int shader_id, const char *uniform, bool b);
void shader_u_float(unsigned int shader_id, const char *uniform, float f);
void shader_u_texture(unsigned int shader_id, const char *uniform,
	unsigned int texture_id, int uniform_index);

#endif
