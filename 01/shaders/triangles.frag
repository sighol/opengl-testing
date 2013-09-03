#version 400

in vec4 exColor;
in float exDist;
out vec4 fColor;


void main() {
	vec4 c = vec4(-exDist+.5, 1-exDist, 1-exDist, 1);
	fColor =  c;
}