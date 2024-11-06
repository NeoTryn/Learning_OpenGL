#version 330 core
out vec4 color;

in vec2 TexCoords;

uniform sampler2D texture1;
//uniform sampler2D texture2;

void main() {
	vec2 newCoords = vec2(TexCoords.x, TexCoords.y * -1.0);
	vec4 newColor = texture(texture1, TexCoords);

	if (newColor.a < 0.1)
		discard;
	
	color = newColor;
}	