#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;

void main() {
    frontColor = vec4(color, 1);
    vec4 vtx = modelViewProjectionMatrix * vec4(vertex.x, vertex.y, vertex.z, 1);
    vtx.z = 1 - vtx.z;
    gl_Position = vtx;
}
