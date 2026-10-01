#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

void main() {
    bool isBlack = int(mod(vtexCoord.s * n, 2)) != int(mod(vtexCoord.t * n, 2));
    fragColor = isBlack ? vec4(0, 0, 0, 1) : vec4(.8, .8, .8, 1);
}
