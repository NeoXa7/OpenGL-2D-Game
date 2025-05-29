#version 330 core
out vec4 FragColor;

in vec2 sprite_texture_coords;

uniform sampler2D sprite_texture;
uniform vec4 sprite_color;

void main() {
	FragColor = texture(sprite_texture, sprite_texture_coords) * vec4(sprite_color);
}