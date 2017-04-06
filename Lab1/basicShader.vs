#version 130

attribute vec3 position;

uniform int mode;
uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(position, 1.0);
	if(mode!=0) {
		if(mode == 1) {
			gl_Position.x = 0.0;
		}
		if(mode == 2) {
			gl_Position.y = 0.0;
		}
		if(mode == 3) {
			gl_Position.z = 0.0;
		}
	}
}