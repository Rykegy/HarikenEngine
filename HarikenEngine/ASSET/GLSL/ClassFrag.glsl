#version 330 core

in vec3 ourColor;
out vec4 color;

void main(){

	gl_Position =  proj * view * model * vec4(position, 1.0f);
	color = vec4(ourColor, 1.0f);

}