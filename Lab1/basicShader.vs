#version 130

attribute vec3 position;

uniform mat4 viewProjection;
uniform int mode;
uniform mat4 transform;

void main() {
	
	vec4 temp = transform * vec4(position, 1.0);
	if(mode!=0) {
		if(mode == 1) {
			temp.x = 0.0;
		}
		if(mode == 2) {
			temp.y = 0.0;
		}
		if(mode == 3) {
			temp.z = 0.0;
		}
	}
	gl_Position = viewProjection * temp;
}