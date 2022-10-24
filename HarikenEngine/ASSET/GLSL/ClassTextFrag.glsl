#version 330 core

in vec2 TexCoords;
in vec3 ourColor;
out vec4 color;

uniform sampler2D inputTexture;

void main(){

	color = texture(inputTexture, TexCoords);
	//if(color.a < 0.25)
        //discard;

}