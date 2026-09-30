#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

const float epsZ = 0.9999;

void main( void ) {
	if (gl_PrimitiveIDIn == 0) {
		gfrontColor = vec4(0, 1, 0, 1);
		gl_Position = vec4(-1, 0, epsZ, 1); EmitVertex();
		gl_Position = vec4(0, 0, epsZ, 1);  EmitVertex();
		gl_Position = vec4(-1, 1, epsZ, 1); EmitVertex();
		gl_Position = vec4(0, 1, epsZ, 1);  EmitVertex();
		EndPrimitive();
		gfrontColor = vec4(1, 1, 0, 1);
		gl_Position = vec4(0, 0, epsZ, 1); EmitVertex();
		gl_Position = vec4(1, 0, epsZ, 1);  EmitVertex();
		gl_Position = vec4(0, 1, epsZ, 1); EmitVertex();
		gl_Position = vec4(1, 1, epsZ, 1);  EmitVertex();
		EndPrimitive();
		gfrontColor = vec4(1, 0, 0, 1);
		gl_Position = vec4(-1, -1, epsZ, 1); EmitVertex();
		gl_Position = vec4(0, -1, epsZ, 1);  EmitVertex();
		gl_Position = vec4(-1, 0, epsZ, 1); EmitVertex();
		gl_Position = vec4(0, 0, epsZ, 1);  EmitVertex();
		EndPrimitive();
		gfrontColor = vec4(0, 0, 1, 1);
		gl_Position = vec4(0, -1, epsZ, 1); EmitVertex();
		gl_Position = vec4(1, -1, epsZ, 1);  EmitVertex();
		gl_Position = vec4(0, 0, epsZ, 1); EmitVertex();
		gl_Position = vec4(1, 0, epsZ, 1);  EmitVertex();
		EndPrimitive();
	}

	for (int i = 0; i < 3; ++i) {
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		vec4 pos = gl_Position / gl_Position.w;
		pos.xy -= 0.5;
		gl_Position = pos * gl_Position.w;
		EmitVertex();
    } EndPrimitive();

    for (int i = 0; i < 3; ++i) {
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		vec4 pos = gl_Position / gl_Position.w;
		pos.x += 0.5; pos.y -= 0.5;
		gl_Position = pos * gl_Position.w;
		EmitVertex();
    } EndPrimitive();

	for (int i = 0; i < 3; ++i) {
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		vec4 pos = gl_Position / gl_Position.w;
		pos.x -= 0.5; pos.y += 0.5;
		gl_Position = pos * gl_Position.w;
		EmitVertex();
    } EndPrimitive();

	for (int i = 0; i < 3; ++i) {
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		vec4 pos = gl_Position / gl_Position.w;
		pos.xy += 0.5;
		gl_Position = pos * gl_Position.w;
		EmitVertex();
    } EndPrimitive();
}
