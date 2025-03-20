#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "globals.h"
#include "consts.h"

#include "result.h"
#include "str.h"
#include "file.h"

// TEST
#include "shader.h"
#include "mesh.h"
#include "vec3.h"
#include "mat4.h"

#define CUBE_VERTS_SZ (12 * 3 * 6)
#define CUBE_IDXS_SZ (12 * 3)

static Result graphic_init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfw_window = glfwCreateWindow(
		INIT_WINDOW_W,
		INIT_WINDOW_H,
		"glow cube",
		NULL,
		NULL
	);
	if (glfw_window == NULL) {
		glfwTerminate();
		return ERR("graphic_init(): glfw init err");
	}
	
	glfwMakeContextCurrent(glfw_window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return ERR("graphic_init(): glad init err");
	}

	glViewport(0, 0, INIT_WINDOW_W, INIT_WINDOW_H);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	return OK;
}

int main(void) {
	HANDLE_MAIN(graphic_init());

	unsigned int shader_main = 0;
	HANDLE_MAIN(shader_new(
		&shader_main,
		"shader/main_v.glsl",
		"shader/main_f.glsl"
	));

	float verts[CUBE_VERTS_SZ] = {
		//Pos         Normal
		-1,  1, -1,   0,  1,  0,  // A TOP
		-1,  1,  1,   0,  1,  0,  // D
		 1,  1,  1,   0,  1,  0,  // C

		-1,  1, -1,   0,  1,  0,  // A
		 1,  1,  1,   0,  1,  0,  // C
		 1,  1, -1,   0,  1,  0,  // B

		-1, -1, -1,   0, -1,  0,  // E BOTTOM
		 1, -1,  1,   0, -1,  0,  // G
		-1, -1,  1,   0, -1,  0,  // H

		-1, -1, -1,   0, -1,  0,  // E
		 1, -1, -1,   0, -1,  0,  // F
		 1, -1,  1,   0, -1,  0,  // G

		-1,  1, -1,  -1,  0,  0,  // A LEFT
		-1, -1,  1,  -1,  0,  0,  // H
		-1,  1,  1,  -1,  0,  0,  // D

		-1,  1, -1,  -1,  0,  0,  // A
		-1, -1, -1,  -1,  0,  0,  // E
		-1, -1,  1,  -1,  0,  0,  // H

		 1,  1, -1,   1,  0,  0,  // B RIGHT
		 1,  1,  1,   1,  0,  0,  // C
		 1, -1,  1,   1,  0,  0,  // G

		 1,  1, -1,   1,  0,  0,  // B
		 1, -1,  1,   1,  0,  0,  // G
		 1, -1, -1,   1,  0,  0,  // F

		-1,  1,  1,   0,  0,  1,  // D FORWARD
		-1, -1,  1,   0,  0,  1,  // H
		 1,  1,  1,   0,  0,  1,  // C

		 1,  1,  1,   0,  0,  1,  // C
		-1, -1,  1,   0,  0,  1,  // H
		 1, -1,  1,   0,  0,  1,  // G

		-1,  1, -1,   0,  0, -1,  // A BACKWARD
		 1,  1, -1,   0,  0, -1,  // B
		-1, -1, -1,   0,  0, -1,  // E

		 1,  1, -1,   0,  0, -1,  // B
		 1, -1, -1,   0,  0, -1,  // F
		-1, -1, -1,   0,  0, -1,  // E
	};
	unsigned int idxs[CUBE_IDXS_SZ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
		19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
	};
	Mesh mesh = mesh_new(verts, CUBE_VERTS_SZ, idxs, CUBE_IDXS_SZ);

	Mat4 view = mat4_look_at(
		vec3_new(0, 1, 0),
		vec3_new(0, 0, 0),
		vec3_new(0, 0, -1)
	);
	Mat4 proj = mat4_perspective(1, 70, 0.01, 300);
	Vec3 light_dir = vec3_normalized(vec3_new(0.3, -0.5, -1));
	printf("%f %f %f\n", light_dir.x, light_dir.y, light_dir.z);

	while (!glfwWindowShouldClose(glfw_window)) {
		glfwPollEvents();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		Mat4 rot = mat4_rot(0, glfwGetTime(), 0);
		Mat4 translate = mat4_translate(0, 0, -6);
		Mat4 model = mat4_mul(translate, rot);
		glUseProgram(shader_main);
		glUniformMatrix4fv(
			glGetUniformLocation(shader_main, "u_model_mat"),
			1,
			GL_TRUE,
			model.data
		);
		glUniformMatrix4fv(
			glGetUniformLocation(shader_main, "u_view_mat"),
			1,
			GL_TRUE,
			view.data
		);
		glUniformMatrix4fv(
			glGetUniformLocation(shader_main, "u_proj_mat"),
			1,
			GL_TRUE,
			proj.data
		);
		glUniform3f(
			glGetUniformLocation(shader_main, "u_light_dir"),
			light_dir.x,
			light_dir.y,
			light_dir.z
		);
		glBindVertexArray(mesh.vao);
		glDrawElements(GL_TRIANGLES, CUBE_IDXS_SZ, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(glfw_window);
	}

	glfwTerminate();
	printf("reached end of main()\n");

	return 0;
}
