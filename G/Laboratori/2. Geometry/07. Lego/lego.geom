#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;

uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform float step = 0.2;

vec3 NX = vec3(1, 0, 0);
vec3 NY = vec3(0, 1, 0);
vec3 NZ = vec3(0, 0, 1);

float r;
vec3 baricenter;
const vec3 Grey = vec3(0.8);

void setPrimitive(mat4 os, vec3 bc, vec3 N) {
	gfrontColor = vec4(Grey * N.z, 1);
	for (int i = 0; i < 4; ++i) {
		gl_Position = modelViewProjectionMatrix *
			vec4(bc.x + os[0][i], bc.y + os[1][i], bc.z + os[2][i], 1); 
		EmitVertex();
	} EndPrimitive();
}

void emitSide(int x, int y, int z) {
	vec4 cx = x == 0 ? vec4(r) : x == 1 ? vec4(r, r, -r, -r) : vec4(-r, r, -r, r);
	vec4 cy = y == 0 ? vec4(r) : y == 1 ? vec4(r, r, -r, -r) : vec4(-r, r, -r, r);
	vec4 cz = z == 0 ? vec4(r) : z == 1 ? vec4(-r, -r, r, r) : vec4(-r, r, -r, r);
	mat4 offset = mat4(cx, cy, cz, vec4(1));
	setPrimitive(offset, baricenter, x == 0 ? NX : y == 0 ? NY : NZ);
	setPrimitive(-offset, baricenter, x == 0 ? -NX : y == 0 ? -NY : -NZ);
}

void main() {
	//if (gl_PrimitiveIDIn != 1) return;
	baricenter = ((gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3).xyz;
	baricenter /= step;
	baricenter = floor(baricenter);
	baricenter *= step;

	NX = normalize(normalMatrix * NX);
	NY = normalize(normalMatrix * NY);
	NZ = normalize(normalMatrix * NZ);
	
	r = step / 2.0;
	emitSide(2, 1, 0); // Front and back
	emitSide(0, 2, 1); // Left and right
	emitSide(2, 0, 1); // Top and Bottom
}
