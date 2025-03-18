#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "globals.h"
#include "result.h"

static Result graphic_init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfw_window = glfwCreateWindow(500, 500, "glow cube", NULL, NULL);
	if (glfw_window == NULL) {
		glfwTerminate();
		return ERR("graphic_init(): glfw init err");
	}
	
	glfwMakeContextCurrent(glfw_window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return ERR("graphic_init(): glad init err");
	}

	glViewport(0, 0, 500, 500);

	return OK;
}

int main(void) {
	HANDLE_MAIN(graphic_init());

	while (!glfwWindowShouldClose(glfw_window)) {
		glfwPollEvents();
		glfwSwapBuffers(glfw_window);
	}

	glfwTerminate();
	printf("reached end of main()\n");

	return 0;
}
