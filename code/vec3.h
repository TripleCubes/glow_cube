#ifndef VEC3_HEADER
#define VEC3_HEADER

struct _Vec3 {
	float x;
	float y;
	float z;
};
typedef struct _Vec3 Vec3;

Vec3 vec3_new(float x, float y, float z);

Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_mul(Vec3 v, float n);
Vec3 vec3_div(Vec3 v, float n);

float vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);

float vec3_len_sqr(Vec3 v);
float vec3_len(Vec3 v);
Vec3 vec3_normalized(Vec3 v);

Vec3 vec3_rot_x(Vec3 v, float rad);
Vec3 vec3_rot_y(Vec3 v, float rad);
Vec3 vec3_rot_z(Vec3 v, float rad);
Vec3 vec3_rot(Vec3 v, float x, float y, float z);

#endif
