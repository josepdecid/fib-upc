#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D map;
uniform float time;
uniform float a = 0.5;

void main() {
    vec4 c = texture(map, vtexCoord);
    vec2 u = vec2(max(c.x, max(c.y, c.z)));
    float theta = 2 * 3.14159265358979323846 * time;
    float cosine = cos(theta), sine = sin(theta);
    u = mat2(
        vec2(cosine, sine),
        vec2(-sine, cosine)
    ) * u;
    vec2 offset = (a/100)*u;
    fragColor = texture(map, vtexCoord + offset);
}
