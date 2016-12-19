#version 150

uniform int vIsGrid;
uniform float vMaxZ;
uniform float vMinZ;

in vec4 exPos;
out vec4 fColor;

vec4 color(float x) {
	float n;
	if (x < 0) {
		return vec4(0, 0, 1,1);
	} else if (x < 0.25) {
		// blå -> turkis
		n = x / 0.25;
		return vec4(0, x / 0.25, 1, 1);
	} else if(x < 0.5) {
		// turkis -> grønn
		n = (x-0.25)/0.25;
		return vec4(0, 1, 1-n, 1);
	} else if (x < 0.75) {
		// grønn -> gul
		n = (x-0.50) / 0.25;
		return vec4(n, 1, 0, 1);
	} else {
		// gul -> rød
		n =  (x - 0.75) / 0.25;
		return vec4(1, 1-n, 0, 0);
	}
	return vec4(1,0,0,0);

}

float normalizer(float x) {
	float diff = vMaxZ - vMinZ;
	return (x - vMinZ) / diff;
}

void main() {
	if (vIsGrid == 0) {
		fColor =  color(normalizer(exPos.z));
	} else {
		vec4 black = vec4(0);
		fColor = black;
	}
}
