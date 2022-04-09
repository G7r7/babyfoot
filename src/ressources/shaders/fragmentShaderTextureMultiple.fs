#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 material_ambient;
uniform vec3 material_diffuse;
uniform vec3 material_specular;
uniform float material_shininess;

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
    vec4 material = vec4(material_ambient + material_diffuse + material_specular, 1.0f);

    if(lightSource) {
        FragColor = material * lightStrength;
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
    float shininess = material_shininess;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;  

    // FragColor = texture(ourTexture, TexCoord) * material * vec4(ambient + diffuse + specular, 1.0f);
    FragColor = material * vec4(ambient + diffuse + specular, 1.0f);
}