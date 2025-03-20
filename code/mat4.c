#include "mat4.h"

#include <string.h>
#include <math.h>
#include "vec3.h"

Mat4 mat4_zero(void) {
	Mat4 m;
	memset(m.data, 0, 16 * sizeof(float));
	return m;
}

Mat4 mat4_new(float *data) {
	Mat4 m;
	memcpy(m.data, data, 16 * sizeof(float));
	return m;
}

Mat4 mat4_mul(Mat4 a, Mat4 b) {
	Mat4 m = mat4_zero();

	for (int y = 0; y < 4; y++) {
	for (int x = 0; x < 4; x++) {
		int i = y * 4 + x;
		int y4 = y * 4;

		float vy0 = a.data[y4];
		float vy1 = a.data[y4 + 1];
		float vy2 = a.data[y4 + 2];
		float vy3 = a.data[y4 + 3];

		float vx0 = b.data[x];
		float vx1 = b.data[4 + x];
		float vx2 = b.data[8 + x];
		float vx3 = b.data[12 + x];

		float dot = vy0 * vx0
		          + vy1 * vx1
		          + vy2 * vx2
		          + vy3 * vx3;

		m.data[i] = dot;
	}
	}

	return m;
}

Mat4 mat4_translate(float x, float y, float z) {
	float data[16] = {
		1.0, 0.0, 0.0, x,
		0.0, 1.0, 0.0, y,
		0.0, 0.0, 1.0, z,
		0.0, 0.0, 0.0, 1.0,
	};
	return mat4_new(data);
}

Mat4 mat4_rot_x(float rad) {
	float data[16] = {
		1.0, 0.0,        0.0,       0.0,
		0.0, cos(rad),  -sin(rad),  0.0,
		0.0, sin(rad),   cos(rad),  0.0,
		0.0, 0.0,        0.0,       1.0,
	};
	return mat4_new(data);
}

Mat4 mat4_rot_y(float rad) {
	float data[16] = {
		 cos(rad),  0.0, sin(rad),  0.0,
		 0.0,       1.0, 0.0,       0.0,
		-sin(rad),  0.0, cos(rad),  0.0,
		 0.0,       0.0, 0.0,       1.0,
	};
	return mat4_new(data);
}

Mat4 mat4_rot_z(float rad) {
	float data[16] = {
		cos(rad),  -sin(rad),  0.0, 0.0,
		sin(rad),   cos(rad),  0.0, 0.0,
		0.0,        0.0,       1.0, 0.0,
		0.0,        0.0,       0.0, 1.0,
	};
	return mat4_new(data);
}

Mat4 mat4_rot(float x, float y, float z) {
	Mat4 a = mat4_mul(mat4_rot_x(x), mat4_rot_y(y));
	return mat4_mul(a, mat4_rot_z(z));
}

Mat4 mat4_scale(float n) {
	float data[16] = {
		n,   0.0, 0.0, 0.0,
		0.0, n,   0.0, 0.0,
		0.0, 0.0, n,   0.0,
		0.0, 0.0, 0.0, 1.0,
	};
	return mat4_new(data);
}

Mat4 mat4_perspective(float aspect, float fov, float near, float far) {
	float data[16] = {
		1.0/(aspect*tan(fov/2.0)), 0.0,              0.0, 0.0,
		0.0,                       1.0/tan(fov/2.0), 0.0, 0.0,
		0.0, 0.0, -(far+near)/(far-near), -(2.0*far*near)/(far-near),
		0.0, 0.0, -1.0,                    0.0,
	};
	return mat4_new(data);
}

Mat4 mat4_look_at(Vec3 up, Vec3 from, Vec3 to) {
	Vec3 z = vec3_normalized(vec3_sub(to, from));
	Vec3 x = vec3_normalized(vec3_cross(z, up));
	Vec3 y = vec3_normalized(vec3_cross(x, z));

	float rot_data[16] = {
		x.x, x.y, x.z, 0.0,
		y.x, y.y, y.z, 0.0,
		-z.x, -z.y, -z.z, 0.0,
		0.0, 0.0, 0.0, 1.0,
	};
	Mat4 rot = mat4_new(rot_data);

	float translate_data[16] = {
		1.0, 0.0, 0.0, -from.x,
		0.0, 1.0, 0.0, -from.y,
		0.0, 0.0, 1.0, -from.z,
		0.0, 0.0, 0.0, 1.0,
	};
	Mat4 translate = mat4_new(translate_data);

	return mat4_mul(rot, translate);
}

Mat4 mat4_transpose(Mat4 a) {
	Mat4 b = mat4_zero();

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			int yx = y * 4 + x;
			int xy = x * 4 + y;
			b.data[yx] = a.data[xy];
		}
	}

	return b;
}
