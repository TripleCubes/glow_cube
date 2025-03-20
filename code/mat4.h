#ifndef MAT4_HEADER
#define MAT4_HEADER

typedef struct _Vec3 Vec3;

struct _Mat4 {
	float data[16];
};
typedef struct _Mat4 Mat4;

Mat4 mat4_zero(void);
Mat4 mat4_new(float *data);

Mat4 mat4_mul(Mat4 a, Mat4 b);

Mat4 mat4_translate(float x, float y, float z);
Mat4 mat4_rot_x(float rad);
Mat4 mat4_rot_y(float rad);
Mat4 mat4_rot_z(float rad);
Mat4 mat4_rot(float x, float y, float z);
Mat4 mat4_scale(float n);

Mat4 mat4_perspective(float aspect, float fov, float near, float far);
Mat4 mat4_look_at(Vec3 up, Vec3 from, Vec3 to);

Mat4 mat4_transpose(Mat4 a);

#endif
