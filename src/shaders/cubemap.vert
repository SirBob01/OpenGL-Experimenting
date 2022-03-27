#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 in_texcoord;

out vec3 texcoord;

uniform mat4 transform;

void main() {
    texcoord = pos;
    gl_Position = transform * vec4(pos, 1.0);
}
