#version 130

uniform vec4 color;
uniform int mode;

void main() {
	if(mode!=0) {
		gl_FragColor = vec4(1.0, 1.0, 1.0, 0.5);
	}
	else {
		gl_FragColor = color;
	}
}