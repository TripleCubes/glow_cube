#include "graphics.h"

#include <stdbool.h>
#include <glad/glad.h>

#include "consts.h"
#include "globals.h"
#include "result.h"

#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "framebuffer.h"
#include "vec3.h"
#include "mat4.h"

#define CUBE_VERTS_SZ (12 * 3 * 8)
#define CUBE_IDXS_SZ  (12 * 3)
#define VIEW_VERTS_SZ 8
#define VIEW_IDXS_SZ  6

static void blur(unsigned int texture_id) {
	glBindVertexArray(view_mesh.vao);

	glBindFramebuffer(GL_FRAMEBUFFER, blur_fb.fbo);
	glClearColor(0, 0, 0, 1);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_blur);
	glUniform2f(
		glGetUniformLocation(shader_blur, "u_window_sz"),
		INIT_WINDOW_W,
		INIT_WINDOW_H
	);
	glUniform1i(
		glGetUniformLocation(shader_blur, "u_vertical"),
		false
	);
	glUniform1i(
		glGetUniformLocation(shader_blur, "u_texture"),
		0
	);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glDrawElements(GL_TRIANGLES, VIEW_IDXS_SZ, GL_UNSIGNED_INT, 0);


	glBindFramebuffer(GL_FRAMEBUFFER, blur_2_fb.fbo);
	glClearColor(0, 0, 0, 1);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	glUniform1i(
		glGetUniformLocation(shader_blur, "u_vertical"),
		true
	);
	glUniform1i(
		glGetUniformLocation(shader_blur, "u_texture"),
		0
	);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, blur_fb.texture_id);

	glDrawElements(GL_TRIANGLES, VIEW_IDXS_SZ, GL_UNSIGNED_INT, 0);
}

Result graphics_init(void) {
	HANDLE(shader_new(
		&shader_main,
		"shader/main_v.glsl",
		"shader/main_f.glsl"
	));
	HANDLE(shader_new(
		&shader_view,
		"shader/view_v.glsl",
		"shader/view_f.glsl"
	));
	HANDLE(shader_new(
		&shader_blur,
		"shader/view_v.glsl",
		"shader/blur_f.glsl"
	));
	HANDLE(shader_new(
		&shader_add,
		"shader/view_v.glsl",
		"shader/add_f.glsl"
	));

	float cube_verts[CUBE_VERTS_SZ] = {
		// pos        normal       uv
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
	unsigned int cube_idxs[CUBE_IDXS_SZ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
		19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
	};
	cube_mesh = mesh_new(
		MESH_3D,
		cube_verts,
		CUBE_VERTS_SZ,
		cube_idxs,
		CUBE_IDXS_SZ
	);

	float view_verts[VIEW_VERTS_SZ] = {
		-1,  1, // A 0
		 1,  1, // B 1
		 1, -1, // C 2
		-1, -1, // D 3
	};
	unsigned int view_idxs[VIEW_IDXS_SZ] = {
		0, // A
		3, // D
		1, // B

		1, // B
		3, // D
		2, // C
	};
	view_mesh = mesh_new(
		MESH_2D,
		view_verts,
		VIEW_VERTS_SZ,
		view_idxs,
		VIEW_IDXS_SZ
	);

	HANDLE(texture_new(&texture, "texture/test.png"));
	HANDLE(framebuffer_new(&scene_fb, INIT_WINDOW_W, INIT_WINDOW_H));
	HANDLE(framebuffer_new(&blur_fb, INIT_WINDOW_W, INIT_WINDOW_H));
	HANDLE(framebuffer_new(&blur_2_fb, INIT_WINDOW_W, INIT_WINDOW_H));
	HANDLE(framebuffer_new(&view_fb, INIT_WINDOW_W, INIT_WINDOW_H));

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
	glBindFramebuffer(GL_FRAMEBUFFER, scene_fb.fbo);
	glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mat4 rot_mat = mat4_rot(0, -glfwGetTime(), 0);
	Mat4 translate_mat = mat4_translate(0, 0, -9);
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


	blur(scene_fb.texture_id);
	blur(blur_2_fb.texture_id);
	blur(blur_2_fb.texture_id);


	glBindFramebuffer(GL_FRAMEBUFFER, view_fb.fbo);
	glClearColor(0, 0, 0, 1);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_add);
	glUniform1f(
		glGetUniformLocation(shader_add, "u_opacity_1"),
		1
	);
	glUniform1f(
		glGetUniformLocation(shader_add, "u_opacity_2"),
		0.8
	);
	glUniform1i(
		glGetUniformLocation(shader_add, "u_texture_1"),
		0
	);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, scene_fb.texture_id);
	glUniform1i(
		glGetUniformLocation(shader_add, "u_texture_2"),
		1
	);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, blur_2_fb.texture_id);

	glBindVertexArray(view_mesh.vao);
	glDrawElements(GL_TRIANGLES, VIEW_IDXS_SZ, GL_UNSIGNED_INT, 0);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0, 0, 0, 1);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_view);
	glUniform1i(
		glGetUniformLocation(shader_view, "u_texture"),
		0
	);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, view_fb.texture_id);

	glBindVertexArray(view_mesh.vao);
	glDrawElements(GL_TRIANGLES, VIEW_IDXS_SZ, GL_UNSIGNED_INT, 0);
}

void graphics_release(void) {
	glDeleteProgram(shader_main);
	glDeleteProgram(shader_view);
	glDeleteProgram(shader_blur);
	glDeleteProgram(shader_add);
	mesh_release(&cube_mesh);
	mesh_release(&view_mesh);
	texture_release(&texture);
	framebuffer_release(&scene_fb);
	framebuffer_release(&blur_fb);
	framebuffer_release(&blur_2_fb);
	framebuffer_release(&view_fb);
}
