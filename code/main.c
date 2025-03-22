#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "globals.h"
#include "consts.h"
#include "result.h"

#include "graphics.h"

static Result init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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
	HANDLE_MAIN(init());

	HANDLE_MAIN(graphics_init());

	while (!glfwWindowShouldClose(glfw_window)) {
		glfwPollEvents();
		draw();
		glfwSwapBuffers(glfw_window);
	}

	graphics_release();
	glfwTerminate();
	printf("reached end of main()\n");

	return 0;
}
