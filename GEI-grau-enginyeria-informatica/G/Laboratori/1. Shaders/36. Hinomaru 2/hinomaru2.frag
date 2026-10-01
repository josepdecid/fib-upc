#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform int nstripes = 16;
uniform vec2 origin = vec2(0, 0);
uniform bool classic = false;

const float phi = 3.14159265358979323846 / 16;
const vec4 red = vec4(1, 0, 0, 1);
const vec4 white = vec4(1, 1, 1, 1);
const vec2 center = vec2(0.5, 0.5);

vec4 drawBackground() {
    if (classic) return red;
    vec2 u = vtexCoord - center;
    float Phi = atan(u.t, u.s);
    return mod(Phi/phi + 0.5, 2) < 1 ? red : white;
}

void main() {
    float dist = distance(center, vtexCoord);
    fragColor = dist <= 0.2 ? red : drawBackground();
}
