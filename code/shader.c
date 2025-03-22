#include "shader.h"

#include <glad/glad.h>
#include <stdio.h>

#include "result.h"
#include "file.h"
#include "str.h"

#include "mat4.h"
#include "vec3.h"

static Result compile_shader(unsigned int *shader, const char *path,
bool is_fragment) {
	Str shader_code;
	char *shader_code_c_str;

	HANDLE(str_cap_new(&shader_code, 4096));
	HANDLE(file_read(&shader_code, path));
	HANDLE(c_str(&shader_code_c_str, &shader_code));

	*shader = glCreateShader(
		is_fragment ? GL_FRAGMENT_SHADER : GL_VERTEX_SHADER
	);
	glShaderSource(*shader, 1, (const char **)(&shader_code_c_str), NULL);
	glCompileShader(*shader);

	str_release(&shader_code);
	free(shader_code_c_str);

	int success = 0;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char info_log[512];
		glGetShaderInfoLog(*shader, 512, NULL, info_log);
		printf("shader compile err\n%s\n%s\n", path, info_log);
		return ERR("compile_shader(): shader compile err");
	}

	return OK;
}

static Result link_shader_program(unsigned int shader_id, const char *v_path,
const char *f_path) {
	unsigned int v_shader;
	unsigned int f_shader;
	HANDLE(compile_shader(&v_shader, v_path, false));
	HANDLE(compile_shader(&f_shader, f_path, true ));

	glAttachShader(shader_id, v_shader);
	glAttachShader(shader_id, f_shader);
	glLinkProgram(shader_id);

	int success = 0;
	glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
	if (!success) {
		char info_log[512];
		glGetProgramInfoLog(shader_id, 512, NULL, info_log);
		printf("shader linking err\n%s\n%s\n%s\n", v_path, f_path, info_log);
		return ERR("link_shader_program(): shader linking err");
	}

	glDeleteShader(v_shader);
	glDeleteShader(f_shader);

	return OK;
}

Result shader_new(unsigned int *shader_id, const char *v_path,
const char *f_path) {
	*shader_id = glCreateProgram();
	HANDLE(link_shader_program(*shader_id, v_path, f_path));
	return OK;
}

void shader_u_mat4(unsigned int shader_id, const char *uniform, const Mat4 *m) {
	glUniformMatrix4fv(
		glGetUniformLocation(shader_id, uniform),
		1,
		GL_TRUE,
		m->data
	);
}

void shader_u_vec3(unsigned int shader_id, const char *uniform, const Vec3 v) {
	glUniform3f(
		glGetUniformLocation(shader_id, uniform),
		v.x,
		v.y,
		v.z
	);
}

void shader_u_2f(unsigned int shader_id, const char *uniform, float a, float b){
	glUniform2f(
		glGetUniformLocation(shader_id, uniform),
		a,
		b
	);
}

void shader_u_bool(unsigned int shader_id, const char *uniform, bool b) {
	glUniform1i(
		glGetUniformLocation(shader_id, uniform),
		b
	);
}

void shader_u_float(unsigned int shader_id, const char *uniform, float f) {
	glUniform1f(
		glGetUniformLocation(shader_id, uniform),
		f
	);
}

void shader_u_texture(unsigned int shader_id, const char *uniform,
unsigned int texture_id, int uniform_index) {
	glUniform1i(
		glGetUniformLocation(shader_id, uniform),
		uniform_index
	);
	glActiveTexture(GL_TEXTURE0 + uniform_index);
	glBindTexture(GL_TEXTURE_2D, texture_id);
}
