#version 330 core

layout (location=0) in vec3 vertex;
layout (location=2) in vec3 color;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

out vec4 frontColor;

void main() {
    frontColor = vec4(color, 1);
    vec3 diff = boundingBoxMax - boundingBoxMin;
    mat4 scale = mat4(
        vec4(diff.x, 0, 0, 0),
        vec4(0, diff.y, 0, 0),
        vec4(0, 0, diff.z, 0),
        vec4(0, 0, 0, 1)
    );
    vec4 center = vec4(boundingBoxMax + boundingBoxMin, 0) / 2;
    vec4 V = scale * vec4(vertex - vec3(0.5), 1);
    gl_Position = modelViewProjectionMatrix * (V + center);
}
