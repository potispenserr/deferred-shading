#version 330 core
out vec4 fragColor;

in vec2 oTexCoord;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

struct Light {
    vec3 position;
    vec3 color;

    float radius;
    float linear;
    float quadratic;
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
        float distance = length(lights[i].position - fragPos);
        if(distance < lights[i].radius){
            vec3 lightDirection = normalize(lights[i].position - fragPos);
            vec3 diffuse = max(dot(normal, lightDirection), 0.0) * albedo * lights[i].color;

            vec3 halfway = normalize(lightDirection + viewDirection);
            float spec = pow(max(dot(normal, halfway), 0.0), 16.0);
            vec3 combinedSpecular = lights[i].color * spec * specular;

            float attenuation = 1.0 / (1.0 + lights[i].linear * distance + lights[i].quadratic * distance * distance);
            diffuse *= attenuation;
            combinedSpecular *= attenuation;
            lightResult += diffuse + combinedSpecular;
        }

        
    }
    fragColor = vec4(lightResult, 1.0);
}