#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

void main() {
    bool isLine = fract(vtexCoord.s * n) < 0.1 || fract(vtexCoord.t * n) < 0.1;
    fragColor = isLine ? vec4(0, 0, 0, 1) : vec4(.8, .8, .8, 1);
}
