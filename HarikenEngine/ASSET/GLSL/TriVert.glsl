#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 color;

out vec3 ourColor;

uniform mat4 model;

void main(){  

	gl_Position = model * vec4(position, 1.0f);
	ourColor = color;

}