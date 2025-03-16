COMPILER := gcc
AR       := ar rvs
BIN_NAME := glow_cube.exe
CODE_DIR := code/
BIN_DIR  := build/bin/
OBJ_DIR  := build/obj/

GLFW_INCLUDES  := -Ilib/glfw-3.3.8/include/
GLAD_INCLUDES  := -Ilib/glad/include/
INCLUDES       := $(GLFW_INCLUDES) $(GLAD_INCLUDES)
LIBS           := $(OBJ_DIR)glfw.a $(OBJ_DIR)glad.a
COMPILER_FLAGS := -Wall -Wextra -Wpedantic -Werror -g3 -MMD -MP

CODE_FILES := $(wildcard $(CODE_DIR)*.c)
OBJ_FILES  := $(CODE_FILES:$(CODE_DIR)%.c=$(OBJ_DIR)%.o)
DEP_FILES  := $(CODE_FILES:$(CODE_DIR)%.c=$(OBJ_DIR)%.d)

GLFW_ALL_PLATS := context.c init.c input.c monitor.c vulkan.c window.c
GLFW_WINDOWS   := win32_init.c win32_joystick.c win32_monitor.c win32_time.c \
                  win32_thread.c win32_window.c wgl_context.c egl_context.c \
                  osmesa_context.c
GLFW_C         := $(GLFW_ALL_PLATS) $(GLFW_WINDOWS)
GLFW_OBJ_FILES := $(GLFW_C:%.c=$(OBJ_DIR)%.o)


all: $(BIN_DIR)$(BIN_NAME)

run: $(BIN_DIR)$(BIN_NAME)
	$(BIN_DIR)$(BIN_NAME)

$(BIN_DIR)$(BIN_NAME): build_dirs $(LIBS) $(OBJ_FILES)
	$(COMPILER) -o $@ $(LIBS) $(OBJ_FILES)

build_dirs:
	-mkdir "build/bin/"
	-mkdir "build/obj/"

$(OBJ_DIR)%.o: $(CODE_DIR)%.c makefile
	$(COMPILER) $(COMPILER_FLAGS) $(INCLUDES) -c -o $@ $<

-include $(DEP_FILES)


$(OBJ_DIR)glfw.a: $(GLFW_OBJ_FILES)
	$(AR) $@ $^

$(GLFW_OBJ_FILES): $(OBJ_DIR)%.o: lib/glfw-3.3.8/src/%.c makefile
	$(COMPILER) $(GLFW_INCLUDES) -D_GLFW_WIN32 -c -o $@ $<

$(OBJ_DIR)glad.a: $(OBJ_DIR)glad.o
	$(AR) $@ $^

$(OBJ_DIR)glad.o: lib/glad/src/glad.c makefile
	$(COMPILER) $(GLAD_INCLUDES) -c -o $@ $<
