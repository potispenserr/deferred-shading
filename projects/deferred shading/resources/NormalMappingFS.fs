#version 430 core
out vec4 FragColor;


in vec3 lightNormal;  
in vec2 TexCoordLight;
in vec3 tangentFragPos;
in vec3 tangentViewPosition;
in vec3 tangentLightPosition;
  

struct Material {
    sampler2D textureDiffuse;
    sampler2D textureNormal;
    vec3 textureSpecular;
    float shininess;
}; 

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};
  
uniform Material material;
uniform Light light;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientIntensity;


void main()
{
    vec3 ambient = light.ambient * texture(material.textureDiffuse, TexCoordLight).rgb;
    
    vec3 norm = texture(material.textureNormal, TexCoordLight).rgb;
    // no transforming normal vector to another range
    
    vec3 lightDirection = normalize(tangentLightPosition - tangentFragPos);
    float distdiff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * distdiff * texture(material.textureDiffuse, TexCoordLight).rgb;
            
    vec3 viewDirection = normalize(tangentViewPosition - tangentFragPos);
    vec3 halfway = normalize(lightDirection + viewDirection);
    float spec = pow(max(dot(norm, halfway), 0.0), material.shininess);
    vec3 combinedSpec = light.specular * (spec * material.textureSpecular);  
    

    vec3 result = ambient + diffuse + combinedSpec;
    FragColor = vec4(result, 1.0);
} 