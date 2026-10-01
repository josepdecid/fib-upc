#version 330 core

in vec3 vertex;
in vec3 color;
out vec4 colorO;

uniform float scale;
uniform mat4 matrix;

void main()  {
    gl_Position = matrix * vec4(2 * vertex, 1.0);
    colorO = vec4(color, 1.0);
}