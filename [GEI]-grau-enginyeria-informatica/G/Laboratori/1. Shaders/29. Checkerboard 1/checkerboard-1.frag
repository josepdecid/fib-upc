#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

void main() {
    bool isBlack = int(8 * fract(vtexCoord.s)) % 2 != int(8 * fract(vtexCoord.t)) % 2;
    fragColor = isBlack ? vec4(0, 0, 0, 1) : vec4(.8, .8, .8, 1);
}
