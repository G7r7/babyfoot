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

void main()
{
    // diffuse lighting calculations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * lightStrength;

    // ambient lighting calculations
    vec3 ambient = lightColor * lightStrength * 0.15 ;

    FragColor = texture(ourTexture, TexCoord) * vec4(ambient + diffuse, 1.0f);
}