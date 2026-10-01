#version 330 core

in vec3 vertex;
in vec3 color;
out vec4 colorO;

uniform float val;
uniform mat4 matrix;

void main()  {
    gl_Position = matrix * vec4(vertex * val, 1.0);
    colorO = vec4(color, 1.0);
}
