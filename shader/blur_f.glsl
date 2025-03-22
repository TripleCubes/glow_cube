#version 330 core
in vec2 f_uv;
out vec4 out_color;

uniform vec2 u_window_sz;
uniform sampler2D u_texture;
uniform bool u_vertical;

void main() {
	vec4 color = vec4(0, 0, 0, 0);

	vec2 px_sz = vec2(1/u_window_sz.x, 1/u_window_sz.y);

	if (!u_vertical) {
		color += texture(u_texture, vec2(f_uv.x - px_sz.x * 7, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x - px_sz.x * 6, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x - px_sz.x * 5, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x - px_sz.x * 4, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x - px_sz.x * 3, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x - px_sz.x * 2, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x - px_sz.x * 1, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x              , f_uv.y));
		color += texture(u_texture, vec2(f_uv.x + px_sz.x * 1, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x + px_sz.x * 2, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x + px_sz.x * 3, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x + px_sz.x * 4, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x + px_sz.x * 5, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x + px_sz.x * 6, f_uv.y));
		color += texture(u_texture, vec2(f_uv.x + px_sz.x * 7, f_uv.y));
	}
	else {
		color += texture(u_texture, vec2(f_uv.x, f_uv.y - px_sz.y * 7));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y - px_sz.y * 6));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y - px_sz.y * 5));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y - px_sz.y * 4));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y - px_sz.y * 3));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y - px_sz.y * 2));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y - px_sz.y * 1));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y              ));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y + px_sz.y * 1));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y + px_sz.y * 2));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y + px_sz.y * 3));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y + px_sz.y * 4));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y + px_sz.y * 5));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y + px_sz.y * 6));
		color += texture(u_texture, vec2(f_uv.x, f_uv.y + px_sz.y * 7));
	}
	color /= 15;
	color.a = 1;

	out_color = color;
}
