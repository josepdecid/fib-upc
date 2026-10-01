#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 NE;
out vec3 VE;
out vec3 LE;

uniform mat4 modelViewMatrix;
uniform mat4 viewMatrixInverse;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform bool world = true;

uniform vec4 lightPosition; // L

void main() {
  vec3 P = world ? vertex : (modelViewMatrix * vec4(vertex, 1)).xyz;

  NE = world ? normal : normalMatrix * normal;
  VE = (world ? (viewMatrixInverse * vec4(0, 0, 0, 1)).xyz : vec3(0)) - P;
  LE = (world ? (viewMatrixInverse * lightPosition).xyz : lightPosition.xyz) - P;

  gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
