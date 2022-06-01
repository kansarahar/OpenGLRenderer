#version 330 core

out vec4 FragColor;
in vec3 color;
in vec2 tex_coord;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;

void main() {
	FragColor = mix(texture(u_texture0, tex_coord), texture(u_texture1, tex_coord), 0.0);
};