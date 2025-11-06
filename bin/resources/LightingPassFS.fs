#version 330 core
out vec4 fragColor;

in vec2 oTexCoord;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

struct Light {
    vec3 position;
    vec3 color;
};

const int numLights = 20;
uniform Light lights[numLights];
uniform vec3 viewPosition;

void main() {
    vec3 fragPos = texture(gPosition, oTexCoord).rgb;
    vec3 normal = texture(gNormal, oTexCoord).rgb;
    vec3 albedo = texture(gAlbedo, oTexCoord).rgb;
    float specular = texture(gAlbedo, oTexCoord).a;

    vec3 lightResult = albedo * 0.1;
    vec3 viewDirection = normalize(viewPosition - fragPos);
    for(int i = 0; i < numLights; ++i){
        vec3 lightDirection = normalize(lights[i].position - fragPos);
        vec3 diffuse = max(dot(normal, lightDirection), 0.0) * albedo * lights[i].color;
        lightResult += diffuse;
    }
    fragColor = vec4(lightResult, 1.0);
}