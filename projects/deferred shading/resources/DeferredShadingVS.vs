#version 330 core
layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 oTexCoord;
out vec3 fragPos;
out vec3 lightNormal;

void main()
{
    vec4 worldPosition = model * vec4(pos, 1.0);

	oTexCoord = texCoord;
	lightNormal = mat3(transpose(inverse(model))) * normal;
	fragPos = worldPosition.xyz;
    oTexCoord = texCoord;
	gl_Position = projection * view *  worldPosition;

}
