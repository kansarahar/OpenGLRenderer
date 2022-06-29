#version 330 core

out vec4 FragColor;
in vec3 color;
in vec2 tex_coord;

uniform float u_ambient_strength;
uniform vec3 u_light_color;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;

void main() {
	FragColor = texture(u_texture0, tex_coord) * vec4(u_ambient_strength * u_light_color, 1.0);
};