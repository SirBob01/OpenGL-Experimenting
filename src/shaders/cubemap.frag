#version 460 core
out vec4 out_color;

in vec3 texcoord;

uniform samplerCube skybox;

void main() {
    out_color = texture(skybox, texcoord);
}
