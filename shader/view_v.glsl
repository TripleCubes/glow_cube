#version 330 core
layout (location = 0) in vec2 v_pos;
out vec2 f_uv;

void main() {
	f_uv = (vec2(v_pos.x, v_pos.y) + vec2(1, 1)) / 2;
	gl_Position = vec4(v_pos, 0, 1);
}
