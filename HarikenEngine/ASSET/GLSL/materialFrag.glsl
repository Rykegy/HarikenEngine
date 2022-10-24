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

struct MTL{

	int diffMap;

	float Ns;
	float Ni;
	float d;
	float Tr;
	vec3 Tf;
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	vec3 Ke;

};

uniform sampler2D inputTexture;
uniform Light light;
uniform MTL mtl;
uniform vec3 viewPosition;

void main(){

	//Ambient
	vec3 ambient = mtl.Ka * texture(inputTexture, TexCoords).rgb * light.color;

	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.pos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * mtl.Kd * texture(inputTexture, TexCoords).rgb * light.color;

	//Specular
	vec3 viewDir = normalize(viewPosition - FragPosition);
	vec3 reflectedDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectedDir), 0.0f), mtl.Ns);
	vec3 specular = spec * mtl.Ks * light.color;

	vec3 result = ambient + diffuse + specular;

	color = vec4(result, mtl.d);

}