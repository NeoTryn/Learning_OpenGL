#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

out vec2 frag_tex;

uniform mat4 trans;

void main() {
    gl_Position = trans * vec4(pos, 1.0);
    frag_tex = tex;
}