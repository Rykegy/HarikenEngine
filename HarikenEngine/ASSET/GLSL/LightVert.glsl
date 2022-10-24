#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 color;

out vec3 Normal;
out vec2 TexCoords;
out vec3 ourColor;
out vec3 FragPosition;

//uniform Light light;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(){

	gl_Position =  proj * view * model * vec4(position, 1.0f);
	TexCoords = texCoords;
	ourColor = color;
	Normal = vec3((transpose(inverse(model)) * vec4(normal, 1.0f)).xyz);
	FragPosition = vec3((model * gl_Position).xyz);

}