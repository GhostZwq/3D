#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 LightingColor;                 // Result Lighting Color

uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 lightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vec3 FragPos = vec3(model * vec4(aPos, 1.0));

	// strenght
	float ambientStrength = 0.1;
	float specularStrength = 1.0;

	// Ambient
	vec3 ambient = ambientStrength * lightColor;
	
	// Diffuse
	vec3 norm = normalize(mat3(transpose(inverse(model))) * aNormal);
	vec3 lightDir = normalize(lightPos - FragPos);	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
	
	LightingColor = ambient + diffuse + specular;	
	
}