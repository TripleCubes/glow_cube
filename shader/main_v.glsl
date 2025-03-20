#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec3 v_normal;
out vec3 f_normal;

uniform mat4 u_model_mat;
uniform mat4 u_view_mat;
uniform mat4 u_proj_mat;

void main() {
	f_normal = normalize((u_model_mat * vec4(v_normal, 1))).xyz;
	gl_Position = u_proj_mat * u_view_mat * u_model_mat * vec4(v_pos, 1);
}
