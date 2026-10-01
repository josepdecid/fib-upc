#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform int nstripes = 16;
uniform vec2 origin = vec2(0, 0);

const vec2 center = vec2(0.5, 0.5);

void main() {
    float dist = distance(center, vtexCoord);
    fragColor = dist <= 0.2 ? vec4(1, 0, 0, 1) : vec4(1, 1, 1, 1);
}
