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

vec4 blinnPhong() {
    vec3 P = (modelViewMatrix * vec4(vertex, 1)).xyz;
    vec3 N = normalize(normalMatrix * normal);
    vec3 V = vec3(0, 0, 1);
    vec3 L = normalize(lightPosition.xyz - P);
    vec3 H = normalize(V + L);

    return matAmbient * lightAmbient + matDiffuse * lightDiffuse * max(0.0, dot(N, L))
        + matSpecular * lightSpecular * pow(max(0.0, dot(N, H)), matShininess);
}

void main() {
    frontColor = blinnPhong();
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
