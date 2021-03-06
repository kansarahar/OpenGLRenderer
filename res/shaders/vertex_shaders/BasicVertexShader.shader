#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec3 a_color;
layout(location = 3) in vec2 a_texcoord;

out vec3 color;
out vec2 tex_coord;

uniform mat4 u_proj;
uniform mat4 u_view;
uniform mat4 u_model;

void main() {
	gl_Position = u_proj * u_view * u_model * vec4(a_pos, 1.0);
	color = a_color;
	tex_coord = a_texcoord;
};