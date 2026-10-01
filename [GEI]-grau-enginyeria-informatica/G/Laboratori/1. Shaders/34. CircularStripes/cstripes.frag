#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform int nstripes = 16;
uniform vec2 origin = vec2(0, 0);

void main() {
    int dist = int(distance(vtexCoord, origin) * nstripes);
    fragColor = mod(dist, 2) == 0 ? vec4(1, 0, 0, 1) : vec4(1, 1, 0, 1);
}
