#ifndef GLOBALS_HEADER
#define GLOBALS_HEADER

#include <GLFW/glfw3.h>

typedef struct _Mesh Mesh;
typedef struct _Texture Texture;
typedef struct _Mat4 Mat4;
typedef struct _Vec3 Vec3;

extern GLFWwindow *glfw_window;

extern unsigned int shader_main;
extern Mesh cube_mesh;
extern Texture texture;

extern Mat4 view_mat;
extern Mat4 proj_mat;
extern Vec3 light_dir;

#endif
