#version 330 core

in vec3 ourColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixLevel;

void main()
{
    vec4 color = vec4(ourColor, 1.0);
    vec4 texture0 = texture(ourTexture0, TexCoord);
    vec4 texture1 = texture(ourTexture1, TexCoord);
    vec4 texture2 = texture(ourTexture2, TexCoord);
    vec4 texture = mix(texture0, texture1, mixLevel);
    FragColor = mix(color, texture, 0.5);
}