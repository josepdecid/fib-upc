#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

const vec4 CYAN = vec4(0, 1, 1, 1);

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

	// Cyan rectangle first time
	if (gl_PrimitiveIDIn == 0) {
		float r = distance(boundingBoxMax, boundingBoxMin) / 2;
		float y = boundingBoxMin.y - 0.01;
		vec3 c = (boundingBoxMax + boundingBoxMin) / 2;
		gfrontColor = CYAN;

		gl_Position = modelViewProjectionMatrix * vec4(c.x + r, y, c.z - r, 1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(c.x - r, y, c.z - r, 1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(c.x + r, y, c.z + r, 1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(c.x - r, y, c.z + r, 1); EmitVertex();
		EndPrimitive();
	}
}
