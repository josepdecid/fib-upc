#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform float dist;

void main() {
	gfrontColor = vfrontColor[0];
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
    EndPrimitive();
}
