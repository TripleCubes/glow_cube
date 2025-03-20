#include "vec3.h"

#include <math.h>

Vec3 vec3_new(float x, float y, float z) {
	Vec3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

Vec3 vec3_add(Vec3 a, Vec3 b) {
	return vec3_new(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
	return vec3_new(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 vec3_mul(Vec3 v, float n) {
	return vec3_new(v.x * n, v.y * n, v.z * n);
}

Vec3 vec3_div(Vec3 v, float n) {
	return vec3_new(v.x / n, v.y / n, v.z / n);
}

float vec3_dot(Vec3 a, Vec3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 vec3_cross(Vec3 a, Vec3 b) {
	return vec3_new(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	);
}

float vec3_len_sqr(Vec3 v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

float vec3_len(Vec3 v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 vec3_normalized(Vec3 v) {
	return vec3_div(v, vec3_len(v));
}

Vec3 vec3_rot_x(Vec3 v, float rad) {
	return vec3_new(
		v.x,
		v.y * cos(rad) - v.z * sin(rad),
		v.y * sin(rad) + v.z * cos(rad)
	);
}

Vec3 vec3_rot_y(Vec3 v, float rad) {
	return vec3_new(
		v.x * cos(rad) - v.z * sin(rad),
		v.y,
		v.x * sin(rad) + v.z * cos(rad)
	);
}

Vec3 vec3_rot_z(Vec3 v, float rad) {
	return vec3_new(
		v.x * cos(rad) - v.y * sin(rad),
		v.x * sin(rad) + v.y * cos(rad),
		v.z
	);
}

Vec3 vec3_rot(Vec3 v, float x, float y, float z) {
	return vec3_rot_z(vec3_rot_y(vec3_rot_x(v, x), y), z);
}
