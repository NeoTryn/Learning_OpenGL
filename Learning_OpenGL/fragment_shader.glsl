#version 330 core
out vec4 color;

in vec2 TexCoords;

uniform sampler2D texture1;

void main() {
	vec2 newCoords = vec2(TexCoords.x, TexCoords.y * -1.0);
	color = texture(texture1, newCoords);	
}	