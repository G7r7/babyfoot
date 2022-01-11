#version 330 core

in vec3 ourColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform float lightStrength;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * (lightColor, 1.0f) * lightStrength;
}