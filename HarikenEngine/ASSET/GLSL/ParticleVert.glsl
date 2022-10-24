#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 color;

//out vec3 Normal;
out vec2 TexCoords;
out vec3 ourColor;
out float intensity;
out float luminence;
out vec3 ltColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float opaqueness;
uniform float brightness;
uniform vec3 myColor;
uniform vec3 lightColor;

void main(){

	gl_Position =  proj * view * model * vec4(position, 1.0f);
	TexCoords = texCoords;
	ourColor = myColor;
	intensity = opaqueness;
	luminence = brightness;
	ltColor = lightColor;

}