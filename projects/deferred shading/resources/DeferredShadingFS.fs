#version 330 core
layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedo;

in vec2 oTexCoord;
in vec3 fragPos;
in vec3 lightNormal;

uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;

void main(){
    gPosition = fragPos;
    gNormal = normalize(lightNormal);
    gAlbedo.rgb = texture(textureDiffuse, oTexCoord).rgb;
    gAlbedo.a = texture(textureSpecular, oTexCoord).r;
}