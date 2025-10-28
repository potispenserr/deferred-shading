#version 430 core
layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoordLight;
out vec4 fragColor;
out vec3 fragPos;
out vec3 lightNormal;
void main()
{
	gl_Position = projection * view *  model * vec4(pos, 1.0);
	TexCoordLight = texCoord;
	lightNormal = mat3(transpose(inverse(model))) * normal;
	fragPos = vec3(model * vec4(pos, 1.0));
}