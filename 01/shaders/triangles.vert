#version 400

layout(location = 0) in vec4 vPosition;

out vec4 vColor;

void main() {
	gl_Position = vPosition;
	vColor = vec4(0.0, 0.8, 0.6, 0.1);
}