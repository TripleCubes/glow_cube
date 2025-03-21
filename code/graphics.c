#include "graphics.h"

#include <glad/glad.h>

#include "globals.h"
#include "result.h"

#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "vec3.h"
#include "mat4.h"

#define CUBE_VERTS_SZ (12 * 3 * 8)
#define CUBE_IDXS_SZ (12 * 3)

Result graphics_init(void) {
	HANDLE(shader_new(
		&shader_main,
		"shader/main_v.glsl",
		"shader/main_f.glsl"
	));

	float verts[CUBE_VERTS_SZ] = {
		-1,  1, -1,   0,  1,  0,   0, 0,  // A TOP
		-1,  1,  1,   0,  1,  0,   0, 1,  // D
		 1,  1, -1,   0,  1,  0,   1, 0,  // B

		 1,  1, -1,   0,  1,  0,   1, 0,  // B
		-1,  1,  1,   0,  1,  0,   0, 1,  // D
		 1,  1,  1,   0,  1,  0,   1, 1,  // C

		-1, -1, -1,   0, -1,  0,   1, 0,  // E BOTTOM
		 1, -1, -1,   0, -1,  0,   0, 0,  // F
		-1, -1,  1,   0, -1,  0,   1, 1,  // H

		 1, -1, -1,   0, -1,  0,   0, 0,  // F
		 1, -1,  1,   0, -1,  0,   0, 1,  // G
		-1, -1,  1,   0, -1,  0,   1, 1,  // H

		-1,  1, -1,  -1,  0,  0,   0, 0,  // A LEFT
		-1, -1,  1,  -1,  0,  0,   1, 1,  // H
		-1,  1,  1,  -1,  0,  0,   1, 0,  // D

		-1,  1, -1,  -1,  0,  0,   0, 0,  // A
		-1, -1, -1,  -1,  0,  0,   0, 1,  // E
		-1, -1,  1,  -1,  0,  0,   1, 1,  // H

		 1,  1, -1,   1,  0,  0,   1, 0,  // B RIGHT
		 1,  1,  1,   1,  0,  0,   0, 0,  // C
		 1, -1,  1,   1,  0,  0,   0, 1,  // G

		 1,  1, -1,   1,  0,  0,   1, 0,  // B
		 1, -1,  1,   1,  0,  0,   0, 1,  // G
		 1, -1, -1,   1,  0,  0,   1, 1,  // F
		 
		-1,  1,  1,   0,  0,  1,   0, 0,  // D TOWARD
		-1, -1,  1,   0,  0,  1,   0, 1,  // H
		 1,  1,  1,   0,  0,  1,   1, 0,  // C

		 1,  1,  1,   0,  0,  1,   1, 0,  // C
		-1, -1,  1,   0,  0,  1,   0, 1,  // H
		 1, -1,  1,   0,  0,  1,   1, 1,  // G

		-1,  1, -1,   0,  0, -1,   1, 0,  // A AWAY
		 1,  1, -1,   0,  0, -1,   0, 0,  // B
		-1, -1, -1,   0,  0, -1,   1, 1,  // E

		 1,  1, -1,   0,  0, -1,   0, 0,  // B
		 1, -1, -1,   0,  0, -1,   0, 1,  // F
		-1, -1, -1,   0,  0, -1,   1, 1,  // E
	};
	unsigned int idxs[CUBE_IDXS_SZ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
		19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
	};
	cube_mesh = mesh_new(verts, CUBE_VERTS_SZ, idxs, CUBE_IDXS_SZ);

	HANDLE(texture_new(&texture, "texture/test.png"));

	view_mat = mat4_look_at(
		vec3_new(0, 1, 0),
		vec3_new(0, 0, 0),
		vec3_new(0, 0, -1)
	);
	proj_mat = mat4_perspective(1, 70, 0.01, 300);
	light_dir = vec3_normalized(vec3_new(0.3, -0.5, -1));

	return OK;
}

void draw(void) {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	Mat4 rot_mat = mat4_rot(0, -glfwGetTime(), 0);
	Mat4 translate_mat = mat4_translate(0, 0, -7);
	Mat4 model_mat = mat4_mul(translate_mat, rot_mat);
	glUseProgram(shader_main);
	glUniformMatrix4fv(
		glGetUniformLocation(shader_main, "u_model_mat"),
		1,
		GL_TRUE,
		model_mat.data
	);
	glUniformMatrix4fv(
		glGetUniformLocation(shader_main, "u_view_mat"),
		1,
		GL_TRUE,
		view_mat.data
	);
	glUniformMatrix4fv(
		glGetUniformLocation(shader_main, "u_proj_mat"),
		1,
		GL_TRUE,
		proj_mat.data
	);
	glUniform3f(
		glGetUniformLocation(shader_main, "u_light_dir"),
		light_dir.x,
		light_dir.y,
		light_dir.z
	);
	glUniform1i(
		glGetUniformLocation(shader_main, "u_texture"),
		0
	);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.id);

	glBindVertexArray(cube_mesh.vao);
	glDrawElements(GL_TRIANGLES, CUBE_IDXS_SZ, GL_UNSIGNED_INT, 0);
}

void graphics_release(void) {
	mesh_release(&cube_mesh);
	texture_release(&texture);
	glDeleteProgram(shader_main);
}
