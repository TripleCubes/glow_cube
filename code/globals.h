#ifndef GLOBALS_HEADER
#define GLOBALS_HEADER

#include <GLFW/glfw3.h>

typedef struct _Mesh Mesh;
typedef struct _Texture Texture;
typedef struct _Framebuffer Framebuffer;
typedef struct _Mat4 Mat4;
typedef struct _Vec3 Vec3;

extern GLFWwindow *glfw_window;

extern unsigned int shader_main;
extern unsigned int shader_view;
extern unsigned int shader_blur;
extern unsigned int shader_add;
extern Mesh cube_mesh;
extern Mesh view_mesh;
extern Texture texture;
extern Framebuffer scene_fb;
extern Framebuffer blur_fb;
extern Framebuffer blur_2_fb;
extern Framebuffer view_fb;

extern Mat4 view_mat;
extern Mat4 proj_mat;
extern Vec3 light_dir;

#endif
