#version 330 core

in vec2 vtexCoord;

out vec4 fragColor;

uniform float time;
uniform sampler2D colorMap;

void main() {
    vec2 C = vec2(0.272, 0.09);
    float r = 0.065;
    if (distance(vtexCoord, C) < r) {
        float c = cos(time), s = sin(time);
        vec2 z = vtexCoord - C;
        z = mat2(vec2(c, -s), vec2(s, c)) * z;
        fragColor = texture(colorMap, z + C);
    } else fragColor = texture(colorMap, vtexCoord);
}
