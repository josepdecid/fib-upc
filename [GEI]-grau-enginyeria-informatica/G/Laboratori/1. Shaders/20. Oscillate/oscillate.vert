#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform float time;

uniform bool eyespace;

void main() {
    float y = eyespace ? (modelViewMatrix * vec4(vertex, 1)).y : vertex.y;
    float r = distance(boundingBoxMax, boundingBoxMin) / 2;
    float d = (r/10)*y;
    vec3 vtx = vertex + d * sin(time) * normal;

    frontColor = vec4(color, 1);
    gl_Position = modelViewProjectionMatrix * vec4(vtx, 1);
}
