#version 330 core

in vec3 gnormal;
out vec4 fragColor;

uniform mat3 normalMatrix;

const vec3 Grey = vec3(0.8);

void main() {
    fragColor = vec4(Grey * normalize(normalMatrix * gnormal).z, 1);
}
