#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 color;

out vec3 vertNormal;
out vec3 lightDir;

struct Light{

	vec3 ambient;
	vec3 pos;
	vec3 color;
	vec3 diffuse;

};

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform Light light;

void main() {
	///vec3 lightPosition = vec3(0.0,0.0,5.0);
	vertNormal = vec3((transpose(inverse(model)) * vec4(normal, 1.0f)).xyz);
	vec4 eyePos = model * vec4(position, 1.0f); /// Create the eye vector 
	lightDir = normalize(light.pos - eyePos.xyz); /// Create the light direction 
	
	gl_Position =  proj * view * model * vec4(position, 1.0f);
}
