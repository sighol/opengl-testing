#version 330
#extension GL_ARB_explicit_attrib_location : enable

uniform float vRotationX;
uniform float vRotationY;
uniform float time;

layout(location = 0) in vec4 vPosition;

out vec4 gColor;

void main() {

	float radx = 1;
	float sx = sin(radx);
	float cx = cos(radx);

	float rady = 1;
	float sy = sin(rady);
	float cy = cos(rady);

	mat4 yTransform = mat4(cy, 0, sy, 0,
							0, 1, 0, 0,
							-sy, 0, cy, 0,
							0, 0, 0, 1);

	mat4 xTransform = mat4(1, 0, 0, 0,
							0, cx, -sx, 0,
							0, sx, cx, 0,
							0, 0, 0, 1);

	vec4 pos = vPosition;
	gColor = (pos+vec4(0.7, 0.7, 0.7, 1))/1.4;

	pos.x = pos.x * (1+sin(((pos.z+1)+time)*5)/6);
	pos.y = pos.y * (1+sin(((pos.x+1)+time+1)*4)/7);

	gl_Position = xTransform * yTransform * pos.xzyw;
}