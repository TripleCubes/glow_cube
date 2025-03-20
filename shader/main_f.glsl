#version 330 core
in vec3 f_normal;
out vec4 out_color;

uniform vec3 u_light_dir;

void main() {
	out_color = vec4(vec3(1, 1, 1) * max(0.2, dot(u_light_dir, f_normal)), 1);
}
