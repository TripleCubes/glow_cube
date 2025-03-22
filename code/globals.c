#include "globals.h"

#include "mesh.h"
#include "texture.h"
#include "framebuffer.h"
#include "mat4.h"
#include "vec3.h"

GLFWwindow *glfw_window;

unsigned int shader_main;
unsigned int shader_view;
unsigned int shader_blur;
unsigned int shader_add;
Mesh cube_mesh;
Mesh view_mesh;
Texture texture;
Framebuffer scene_fb;
Framebuffer blur_fb;
Framebuffer blur_2_fb;
Framebuffer view_fb;

Mat4 view_mat;
Mat4 proj_mat;
Vec3 light_dir;
