#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPosition;
out vec4 color;

struct Light{

	float ambient;
	vec3 pos;
	vec3 color;
	float diffuse;

};

uniform sampler2D inputTexture;
uniform Light light;
uniform vec3 viewPosition;

void main(){

	//Ambient
	vec3 ambient = light.ambient * texture(inputTexture, TexCoords).rgb * light.color;

	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.pos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * texture(inputTexture, TexCoords).rgb * light.color;

	//Specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPosition - FragPosition);
	vec3 reflectedDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectedDir), 0.0f), 32.0f);
	vec3 specular = specularStrength * spec * light.color;

	vec3 result = ambient + diffuse + specular;

	color = vec4(result, 1.0f);

}