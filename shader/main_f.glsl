#version 330 core
in vec2 f_uv;
in vec3 f_normal;
out vec4 out_color;

uniform vec3 u_light_dir;
uniform sampler2D u_texture;

void main() {
	vec4 color = texture(u_texture, f_uv);
	out_color = vec4(color.xyz * max(0.2, dot(u_light_dir, f_normal)), 1);
}
