#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D foot0;
uniform sampler2D foot1;
uniform sampler2D foot2;
uniform sampler2D foot3;

const float R = 80.0;

uniform int layer = 1;

uniform vec2 mousePosition;
uniform bool virtualMouse = false;
uniform float mouseX, mouseY; 

vec2 mouse() {
	if (virtualMouse) return vec2(mouseX, mouseY);
	else return mousePosition;
}

void main() {
	float d = distance(gl_FragCoord.xy, mouse());
	fragColor = texture(foot0, vtexCoord);
	if (d < R) {
		vec4 D;
		switch (layer) {
			case 1:
				D = texture(foot1, vtexCoord); break;
			case 2:
				D = texture(foot2, vtexCoord); break;
			case 3:
				D = texture(foot3, vtexCoord); break;
			default:
				D = texture(foot0, vtexCoord);
		}
		fragColor = mix(D, fragColor, d/R);
	}
}