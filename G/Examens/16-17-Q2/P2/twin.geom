#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

void main() {
    for (int i = 0; i < 3; ++i) {
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		vec4 pos = gl_Position / gl_Position.w;
		pos.x += 0.5;
		gl_Position = pos * gl_Position.w;
		EmitVertex();
    } EndPrimitive();

    for (int i = 0; i < 3; ++i) {
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		vec4 pos = gl_Position / gl_Position.w;
		pos.x -= 0.5;
		gl_Position = pos * gl_Position.w;
		EmitVertex();
    } EndPrimitive();
}
