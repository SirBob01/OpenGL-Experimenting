#version 460 core

in vec2 texcoord;

out vec4 out_color;

uniform sampler2D texdata;
uniform int ticker;

void main() {
    out_color = texture(texdata, texcoord);
}
