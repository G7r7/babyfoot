#version 330 core

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform float lightStrength;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{
    // ambient lighting calculations
    vec3 ambient = lightColor * lightStrength * 0.1 ;

    // diffuse lighting calculations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * lightStrength;

    // specular lighting calculations
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float shininess = 32.0;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;  

    FragColor = texture(ourTexture, TexCoord) * vec4(ambient + diffuse + specular, 1.0f);
}