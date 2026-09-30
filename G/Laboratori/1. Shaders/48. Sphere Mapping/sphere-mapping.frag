#version 330 core

in vec3 V;
in vec3 N;
in vec3 O;

out vec4 fragColor;

uniform vec4 lightPosition;
uniform sampler2D texture0;

vec4 sphereMapTex(sampler2D tex, vec3 R) {
    float z = sqrt((R.z + 1)/2);
    vec2 st = vec2(
        (R.x/(2*z) + 1)/2,
        (R.y/(2*z) + 1)/2
    );
    return texture(tex, st);
}

void main() {
    vec3 NN = normalize(N);
    vec3 L = normalize(O - V);
    vec3 R = 2 * max(0, dot(NN, L)) * NN - L;
    fragColor = sphereMapTex(texture0, R);
}
