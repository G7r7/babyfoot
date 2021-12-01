#version 330 core

in vec3 ourColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixLevel;

void main()
{
    // 0.4 : 40% first Texture and 60% second Texture
    FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(-TexCoord.x, TexCoord.y)), mixLevel);  
}