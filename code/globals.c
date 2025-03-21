#include "globals.h"

#include "mesh.h"
#include "texture.h"
#include "mat4.h"
#include "vec3.h"

GLFWwindow *glfw_window;

unsigned int shader_main;
Mesh cube_mesh;
Texture texture;

Mat4 view_mat;
Mat4 proj_mat;
Vec3 light_dir;
