#version 330 core

in vec2 vtexCoord;
in vec3 N;

out vec4 fragColor;

uniform sampler2D window;
uniform sampler2D interior1;
uniform sampler2D exterior2;

void main() {
    vec4 C = texture(window, vtexCoord);
    if (C.a == 1) fragColor = C;
    else {
        vec4 D = texture(interior1, vtexCoord + 0.5 * N.xy);
        if (D.a == 1) fragColor = D;
        else fragColor = texture(exterior2, vtexCoord + 0.7 * N.xy);
    }
}
