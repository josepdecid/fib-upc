#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float speed = 0.5;
uniform float time;

void setTreatment(bool keepTriangles) {
	if (keepTriangles) {
		for (int i = 0; i < 3; ++i) {
			gfrontColor = vfrontColor[i];
			gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
			EmitVertex();
		}
	} else {
		float newPos = fract(time * speed);
		vec4 bar = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3;
		for (int i = 0; i < 3; ++i) {
			gfrontColor = vfrontColor[i];
			gl_Position = modelViewProjectionMatrix * (newPos < 0.5 ?
				mix(gl_in[i].gl_Position, bar, newPos) : mix(bar, gl_in[i].gl_Position, newPos));
			EmitVertex();
		}
	}
}

void main( void ) {
	bool firstTreat = int(mod(time * speed, 2)) == 0;
	bool firstHalf = gl_PrimitiveIDIn % 2 == 0;
	if (firstHalf) setTreatment(firstTreat); else setTreatment(!firstTreat);
    EndPrimitive();
}
