#version 330 core

in vec2 TexCoords;
in vec3 ourColor;
in float intensity;
in float luminence;
in vec3 ltColor;

out vec4 color;

uniform sampler2D inputTexture;

void main(){

	vec4 light = vec4(ltColor.x, ltColor.y, ltColor.z, 1.0f);
	//vec4 light = vec4(0.25f * ourColor[0] + 0.75f, 0.25f * ourColor[1] + 0.75f, 0.25f * ourColor[2] + 0.75f, texture(inputTexture, TexCoords)[3]);
	vec4 fade = vec4(ourColor[0], ourColor[1], ourColor[2], texture(inputTexture, TexCoords)[3] * intensity);
	color = mix(fade, light, texture(inputTexture, TexCoords)[3] * luminence);
	color[3] = color[3];
	//color = texture(inputTexture, TexCoords);
	//color = mix(vec4(ourColor.x, ourColor.y, ourColor.z, lightIntensity * texture(inputTexture, TexCoords)[3]), vec4(lightIntensity, lightIntensity, lightIntensity, lightIntensity * texture(inputTexture, TexCoords)[3]), texture(inputTexture, TexCoords)[3]);
	//if(color.a < 0.25)
        //discard;

}