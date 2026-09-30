#version 330 core

in vec2 vtexCoord;

out vec4 fragColor;

void main() {
    bool isYellow = mod(int(fract(vtexCoord.s) * 9), 2) == 0;
    fragColor = isYellow ? vec4(1, 1, 0, 1) : vec4(1, 0, 0, 1);
}
