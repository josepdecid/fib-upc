#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec3 vNormal[];
out vec3 gnormal;
out vec4 gpos;

uniform mat4 modelViewProjectionMatrix;
uniform float d = 0.1;

vec3 N;

void emitBaseTriangle() {
	gnormal = N;
	for (int i = 0; i < 3; ++i) {
		gpos = gl_in[i].gl_Position;
		gl_Position = modelViewProjectionMatrix * gpos;
		EmitVertex();
	} EndPrimitive();
}

void emitSideSquare(vec4 a, vec4 b) {
	gnormal = cross((b - a).xyz, N);
	gpos = a; gl_Position = modelViewProjectionMatrix * a; EmitVertex();
	gpos = b; gl_Position = modelViewProjectionMatrix * b; EmitVertex();
	a = vec4(a.xyz + d * N, 1); b = vec4(b.xyz + d * N, 1);
	gpos = a; gl_Position = modelViewProjectionMatrix * a; EmitVertex();
	gpos = b; gl_Position = modelViewProjectionMatrix * b; EmitVertex();
	EndPrimitive();
}

void main() {
	N = normalize((vNormal[0] + vNormal[1] + vNormal[2]) / 3);
	emitBaseTriangle();
	emitSideSquare(gl_in[0].gl_Position, gl_in[1].gl_Position);
	emitSideSquare(gl_in[1].gl_Position, gl_in[2].gl_Position);
	emitSideSquare(gl_in[2].gl_Position, gl_in[0].gl_Position);

}
