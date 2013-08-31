#version 400

uniform Uniforms {
	vec3 translation;
	float scale;
	vec4 rotation;
	bool enabled;
};

uniform float vScale;

in vec4 vPosition;
out vec4 vColor;


void main() {
	float scale = 0.01;
	if (vScale > 0) {
		scale = vScale;
	}
	gl_Position = scale * vPosition;
	vColor = vec4(1.0*scale, 1-scale*0.5, 0.2*scale, 1.0);
}