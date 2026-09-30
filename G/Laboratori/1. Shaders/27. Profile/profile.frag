#version 330 core

in vec4 frontColor;
in vec3 V;
in vec3 N;

out vec4 fragColor;

uniform float epsilon = 0.1;
uniform float light = 0.5;

void main() {
    fragColor = (abs(dot(normalize(V), normalize(N))) < epsilon)
        ? vec4(.7, .6, 0, 1) : frontColor * light;
}
