#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 gColor[3];
out vec4 fColor;

void main() {
	vec3 cam = vec3(0, 0, 1);
	vec3 normal = cross(gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz);
	float intensity = dot(cam, normalize(normal));

  for(int i = 0; i < 3; i++)
  {
	fColor = gColor[i]*intensity;
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
  }
  EndPrimitive();
}