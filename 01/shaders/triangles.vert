#version 400

uniform Uniforms {
	vec3 translation;
	float scale;
	vec4 rotation;
	bool enabled;
};

uniform float vScale;
uniform int vRotationX;
uniform int vRotationY;

in vec4 vPosition;
in vec4 vColor;

out vec4 exColor;


void main() {
	float scale = 0.01;
	if (vScale > 0) {
		scale = vScale;
	}
	float radx = radians(vRotationY);
	float sx = sin(radx);
	float cx = cos(radx);

	float rady = radians(vRotationX);
	float sy = sin(rady);
	float cy = cos(rady);

	mat4 yTransform = mat4(cy,  0,  sy,  0,
						   0,   1,   0,  0,
						  -sy,  0,  cy,  0,
						   0,   0,   0,  1);

	mat4 xTransform = mat4(1, 0,    0, 0,
						   0, cx, -sx, 0,
						   0, sx,  cx, 0,
						   0, 0,    0, 1);
	gl_Position = xTransform * yTransform * vPosition;
	exColor = 1 * vColor;
}