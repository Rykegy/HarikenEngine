#version 330 core

in vec3 ourColor;
in vec3 Normal;
out vec4 color;

void main(){

	color = vec4(ourColor, 1.0f);

	if(sqrt(pow(Normal.z, 2)) < 0.5f)
		color = vec4(0.0f, 0.0f, 0.0f, 1.0f);

}