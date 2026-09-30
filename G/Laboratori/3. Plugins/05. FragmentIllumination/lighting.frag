#version 330 core

in vec3 NE;
in vec3 P;

out vec4 fragColor;

uniform vec4 matAmbient, matDiffuse, matSpecular; // Ka, Kd, Ks
uniform float matShininess; // s
uniform vec4 lightAmbient, lightDiffuse, lightSpecular; // Ia, Id, Is
uniform vec4 lightPosition; // L

vec4 phong() {
    vec3 N = normalize(NE);
    vec3 V = normalize(-P);
    vec3 L = normalize(lightPosition.xyz - P);

    float aux = max(0.0, dot(N, L));
    vec3 R = 2.0 * aux * N - L;
    float aux2 = aux > 0 ? pow(max(0.0, dot(R, V)), matShininess) : 0;

    return matAmbient * lightAmbient + matDiffuse * lightDiffuse * aux
        + matSpecular * lightSpecular * aux2;
}

void main() {
    fragColor = phong();
}
