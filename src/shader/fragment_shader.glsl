#version 330 core
out vec4 color;

in vec2 frag_tex;

uniform sampler2D tex;

void main() {
    color = texture(tex, frag_tex);
}