#version 330 core

out vec4 FragColor;

void main() {
    if ((int(gl_FragCoord.y) / 15) % 2 == 0) {
	    if (gl_FragCoord.x < 500)
	    	if (gl_FragCoord.y > 300)
		    	FragColor = vec4(0.851, 0.325, 0.309, 1);
	    	else FragColor = vec4(1, 1, 0.4, 1);
	    else
	    	if (gl_FragCoord .y > 300)
	    		FragColor = vec4(0.357, 0.753, 0.87, 1);
	    	else FragColor = vec4(0.357, 0.753, 0.357, 1);
    } else FragColor = vec4(0.5, 0.7, 1.0, 1.);
}

