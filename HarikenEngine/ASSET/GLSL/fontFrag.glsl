#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D inputTexture;
uniform vec3 myColor;

void main(){

	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(inputTexture, TexCoords).r);
    color = vec4(myColor, 1.0) * sampled;


}