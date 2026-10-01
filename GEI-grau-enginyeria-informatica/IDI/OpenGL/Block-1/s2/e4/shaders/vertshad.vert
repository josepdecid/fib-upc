#version 330 core

in vec3 vertex;
in vec3 color;
out vec4 colorO;

void main()  {
    gl_Position = vec4 (vertex*0.5, 1.0);
    colorO = vec4(color, 1.0);
}
