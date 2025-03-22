#version 330 core
in vec2 f_uv;
out vec4 out_color;

uniform sampler2D u_texture_1;
uniform sampler2D u_texture_2;
uniform float u_opacity_1;
uniform float u_opacity_2;

void main() {
	vec4 color = texture(u_texture_1, f_uv) * u_opacity_1
	           + texture(u_texture_2, f_uv) * u_opacity_2;
	out_color = vec4(color.xyz, 1);
}
