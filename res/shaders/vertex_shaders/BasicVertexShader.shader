#version 330 core

in vec3 a_pos;
in vec3 a_color;
in vec2 a_texcoord;

out vec3 color;
out vec2 tex_coord;

uniform mat4 u_transform;

void main() {
	gl_Position = u_transform * vec4(a_pos, 1.0);
	color = a_color;
	tex_coord = a_texcoord;
};