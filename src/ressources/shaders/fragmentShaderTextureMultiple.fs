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

// uniform sampler2D ourTexture;
uniform bool lightSource;
uniform vec3 lightColor;
uniform float lightStrength;
uniform vec3 lightPos;
uniform vec3 cameraPos;

out vec4 FragColor;

void main()
{
    // material
    vec4 material_vec = vec4(material.ambient + material.diffuse + material.specular, 1.0f);

    if(lightSource) {
        FragColor = material_vec * lightStrength;
        return;
    }

    // ambient lighting calculations
    float ambientStrength = 0.1;
    vec3 ambient = lightColor * lightStrength * ambientStrength;

    // diffuse lighting calculations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * lightStrength;

    // specular lighting calculations
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float shininess = material.shininess;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;  

    // FragColor = texture(ourTexture, TexCoord) * material * vec4(ambient + diffuse + specular, 1.0f);
    FragColor = material_vec * vec4(ambient + diffuse + specular, 1.0f);
}