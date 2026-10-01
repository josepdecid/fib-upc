#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;
uniform vec3 boundingBoxMin;

void main() {
	// Object
	for (int i = 0; i < 3; i++) {
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
	
	// Shadow
	for (int i = 0; i < 3; i++) {
		gfrontColor = vec4(0, 0, 0, 1);
		vec4 pos = modelViewProjectionMatrixInverse * gl_in[i].gl_Position;
		pos.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * pos;
		EmitVertex();
	}
    EndPrimitive();
}
