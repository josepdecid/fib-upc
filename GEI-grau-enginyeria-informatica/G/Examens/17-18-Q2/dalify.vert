#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform float t = 0.4;
uniform float scale = 4.0;

void main() {
    float c = t * (boundingBoxMax.y - boundingBoxMin.y) + boundingBoxMin.y;
    vec3 vtx = vertex;
    if (vtx.y < c) {
        vtx.y *= scale;
    } else {
        float delta = c*scale - c;
        vtx.y += delta;
    }

    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color, 1) * N.z;
    gl_Position = modelViewProjectionMatrix * vec4(vtx, 1);
}
