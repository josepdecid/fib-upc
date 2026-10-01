#version 330 core

in vec4 gfrontColor;
out vec4 fragColor;

uniform sampler2D lego;

void main() {
    fragColor = gfrontColor;
}
