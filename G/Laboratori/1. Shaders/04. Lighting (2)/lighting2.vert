#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform vec4 matAmbient, matDiffuse, matSpecular; // Ka, Kd, Ks
uniform float matShininess; // s
uniform vec4 lightAmbient, lightDiffuse, lightSpecular; // Ia, Id, Is
uniform vec4 lightPosition; // L

vec4 phong() {
    vec3 P = (modelViewMatrix * vec4(vertex, 1)).xyz;
    vec3 N = normalize(normalMatrix * normal);
    vec3 V = normalize(-P);
    vec3 L = normalize(lightPosition.xyz - P);

    float aux = max(0.0, dot(N, L));
    vec3 R = 2.0 * aux * N - L;
    float aux2 = aux > 0 ? pow(max(0.0, dot(R, V)), matShininess) : 0;

    return matAmbient * lightAmbient + matDiffuse * lightDiffuse * aux
        + matSpecular * lightSpecular * aux2;
}

void main() {
    frontColor = phong();
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
