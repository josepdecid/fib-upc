#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D skeletons;

void main() {    
    fragColor = 1 - texture(skeletons, vtexCoord);
}
