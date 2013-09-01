#version 400

uniform Uniforms {
	vec3 translation;
	float scale;
	vec4 rotation;
	bool enabled;
};

uniform float vScale;

in vec4 vPosition;
in vec4 vColor;

out vec4 exColor;


void main() {
	float scale = 0.01;
	if (vScale > 0) {
		scale = vScale;
	}
	gl_Position = scale * vPosition;
	exColor = scale * vColor;
}