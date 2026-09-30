 #version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec3 frontColor;
out vec3 vtx;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

void main() {
    frontColor = color;
    vtx = (modelViewMatrix * vec4(vertex, 1)).xyz;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1);
}
