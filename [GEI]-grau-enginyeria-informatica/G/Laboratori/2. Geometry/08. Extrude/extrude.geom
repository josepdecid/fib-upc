#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec3 vNormal[];
out vec3 gnormal;

uniform mat4 modelViewProjectionMatrix;
uniform float d = 0.5;

vec3 N;

void emitBaseTriangle(bool up) {
	gnormal = up ? N : -N;
	for (int i = 0; i < 3; ++i) {
		vec4 v = gl_in[i].gl_Position;
		if (up) v.xyz += d * N;
		gl_Position = modelViewProjectionMatrix * v;
		EmitVertex();
	} EndPrimitive();
}

void emitSideSquare(vec4 a, vec4 b) {
	gnormal = cross((b - a).xyz, N);
	gl_Position = modelViewProjectionMatrix * a; EmitVertex();
	gl_Position = modelViewProjectionMatrix * b; EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(a.xyz + d * N, 1); EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(b.xyz + d * N, 1); EmitVertex();
	EndPrimitive();
}

void main() {
	N = normalize((vNormal[0] + vNormal[1] + vNormal[2]) / 3);
	emitBaseTriangle(true);
	emitBaseTriangle(false);
	emitSideSquare(gl_in[0].gl_Position, gl_in[1].gl_Position);
	emitSideSquare(gl_in[1].gl_Position, gl_in[2].gl_Position);
	emitSideSquare(gl_in[2].gl_Position, gl_in[0].gl_Position);

}
