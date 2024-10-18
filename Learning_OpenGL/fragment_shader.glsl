#version 330 core
out vec4 color;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
	vec2 newCoords = vec2(TexCoords.x, TexCoords.y * -1.0);
	color = mix(texture(texture1, newCoords), texture(texture2, newCoords), 0.5);	
}	