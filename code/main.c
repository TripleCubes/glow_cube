#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "globals.h"
#include "consts.h"

#include "result.h"
#include "str.h"
#include "file.h"

#include "shader.h"
#include "vao.h"

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
	glCullFace(GL_FRONT);

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

	float verts[9] = {
		 0  ,  0.5,  0  ,
		 0.5, -0.5,  0  ,
		-0.5, -0.5,  0  ,
	};
	unsigned int idxs[3] = {
		0, 1, 2,
	};
	unsigned int vao = vao_new(verts, 9, idxs, 3);


	while (!glfwWindowShouldClose(glfw_window)) {
		glfwPollEvents();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_main);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(glfw_window);
	}

	glfwTerminate();
	printf("reached end of main()\n");

	return 0;
}
