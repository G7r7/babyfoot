#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_ambient;
uniform sampler2D texture_specular;
uniform sampler2D texture_height;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float strength;
};
uniform Light light; 

struct Camera {
    vec3 position;
    vec3 front;
    vec3 up;
    mat4 view;
    mat4 projection;
};
uniform Camera camera;

// Optionnal states
uniform bool lightSource;
uniform bool glowing;

out vec4 FragColor;

void main()
{
    if(lightSource) {
        FragColor = light.strength * vec4(material.ambient + material.diffuse + material.specular, 1.0f);
        return;
    }

    // ambient lighting calculations
    vec3 ambient = light.ambient;

    // diffuse lighting calculations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * (light.diffuse *  material.diffuse);

    // specular lighting calculations
    vec3 viewDir = normalize(camera.position - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec  * material.specular);  

    FragColor = light.strength * (vec4(ambient + diffuse + specular, 1.0f) + texture(texture_diffuse, TexCoord));

    if(glowing) {
        FragColor = FragColor * vec4(0.0, 1.0, 0.0, 1.0);    
    }

}