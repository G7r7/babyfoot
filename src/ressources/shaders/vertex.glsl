#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

struct Camera {
    vec3 position;
    vec3 front;
    vec3 up;
    mat4 view;
    mat4 projection;
};
uniform Camera camera;
uniform mat4 transformation;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = camera.projection * camera.view * transformation * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(transformation))) * aNormal; 
    FragPos = vec3(transformation * vec4(aPos, 1.0));
}