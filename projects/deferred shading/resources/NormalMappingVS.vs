#version 430 core
layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;
layout(location=3) in vec4 tangent;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPosition;
uniform vec3 lightPosition;

out vec2 TexCoordLight;
out vec4 fragColor;
out vec3 tangentFragPos;
out vec3 lightNormal;
out vec3 tangentViewPosition;
out vec3 tangentLightPosition;
void main()
{
	gl_Position = projection * view *  model * vec4(pos, 1.0);
	TexCoordLight = texCoord;
	lightNormal = mat3(transpose(inverse(model))) * normal;
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 fragPos = vec3(model * vec4(pos, 1.0));

	vec3 T = normalize(normalMatrix * vec3(tangent));
	vec3 N = normalize(normalMatrix * normal);
	vec3 B = cross(N, T);
	mat3 TBN = transpose(mat3(T, B, N));
    tangentViewPosition = TBN * viewPosition;
    tangentLightPosition = TBN * lightPosition;
    tangentFragPos = TBN * fragPos;
}
