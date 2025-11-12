#version 330 core
out vec4 fragColor;

in vec2 oTexCoord;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

struct DirectionLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

struct Light {
    vec3 position;
    vec3 color;

    float radius;
    float linear;
    float quadratic;
};

const int numLights = 20;
uniform Light lights[numLights];
uniform DirectionLight directionLight;
uniform vec3 viewPosition;

vec3 calculateDirectionLight(DirectionLight light, vec3 normal, vec3 viewDirection);

vec3 calculatePointLight(Light pointLight, vec3 fragPos, vec3 normal, vec3 viewDirection, int index);

void main() {
    vec3 fragPos = texture(gPosition, oTexCoord).rgb;
    vec3 normal = texture(gNormal, oTexCoord).rgb;
    vec3 albedo = texture(gAlbedo, oTexCoord).rgb;
    float specular = texture(gAlbedo, oTexCoord).a;

    vec3 lightResult = albedo * 0.1;
    vec3 viewDirection = normalize(viewPosition - fragPos);

    //Direction light pass
    lightResult += calculateDirectionLight(directionLight, normal, viewDirection);
    //Point light pass
    for(int index = 0; index < numLights; ++index){
        float distance = length(lights[index].position - fragPos);
        if(distance < lights[index].radius){
            vec3 lightDirection = normalize(lights[index].position - fragPos);
            vec3 diffuse = max(dot(normal, lightDirection), 0.0) * texture(gAlbedo, oTexCoord).rgb * lights[index].color;

            vec3 halfway = normalize(lightDirection + viewDirection);
            float preSpec = pow(max(dot(normal, halfway), 0.0), 16.0);
            vec3 combinedSpecular = lights[index].color * preSpec * texture(gAlbedo, oTexCoord).a;

            float attenuation = 1.0 / (1.0 + lights[index].linear * distance + lights[index].quadratic * distance * distance);
            diffuse *= attenuation;
            combinedSpecular *= attenuation;
            lightResult += diffuse + combinedSpecular;
        }
    }
    // for(int index = 0; index < numLights; ++index){
    //     lightResult += calculatePointLight(lights[index], fragPos, normal, viewDirection, index);
    // }

    
    fragColor = vec4(lightResult, 1.0);
}

vec3 calculateDirectionLight(DirectionLight light, vec3 normal, vec3 viewDirection){
    vec3 lightDirection = normalize(-light.direction);

    float diffuse = max(dot(normal, lightDirection), 0.0);

    vec3 reflectDirection = reflect(-lightDirection, normal);

    float preSpec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32.0);

    vec3 ambient = light.ambient * vec3(texture(gAlbedo, oTexCoord).rgb);
    vec3 combinedDiffuse = light.diffuse * diffuse * vec3(texture(gAlbedo, oTexCoord).rgb);
    vec3 combinedSpecular = light.specular * preSpec * vec3(texture(gAlbedo, oTexCoord).a);
    return (ambient + combinedDiffuse + combinedSpecular);
}

vec3 calculatePointLight(Light pointLight, vec3 fragPos, vec3 normal, vec3 viewDirection, int index){
    vec3 lightResult;
    float distance = length(lights[index].position - fragPos);
    if(distance < lights[index].radius){
        vec3 lightDirection = normalize(lights[index].position - fragPos);
        vec3 diffuse = max(dot(normal, lightDirection), 0.0) * texture(gAlbedo, oTexCoord).rgb * lights[index].color;

        vec3 halfway = normalize(lightDirection + viewDirection);
        float preSpec = pow(max(dot(normal, halfway), 0.0), 16.0);
        vec3 combinedSpecular = lights[index].color * preSpec * texture(gAlbedo, oTexCoord).a;

        float attenuation = 1.0 / (1.0 + lights[index].linear * distance + lights[index].quadratic * distance * distance);
        diffuse *= attenuation;
        combinedSpecular *= attenuation;
        lightResult += diffuse + combinedSpecular;
        return lightResult;
    }
}