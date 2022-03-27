#version 460 core

in vec2 texcoord;

out vec4 out_color;

uniform sampler2D specular;
uniform sampler2D diffuse;
uniform sampler2D normal;

void main() {
    vec4 texcolor = texture(diffuse, texcoord);
    out_color = texcolor;
}
