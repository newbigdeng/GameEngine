#version 330 core
//in vec3 vColor;
in vec2 vUV;
in vec3 vNormal;
in vec3 vFragPos;
out vec4 FragColor;

struct Light
{
	vec3 color;
	vec3 position;
};
uniform Light uLight;
uniform vec3 uCameraPos;

uniform sampler2D brick;
uniform sampler2D baseColor;
uniform vec4 uColor;


void main()
{
	vec3 ambient = vec3(0.18f);

	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(uLight.position - vFragPos);

	float diff = max(dot(norm, lightDir),0.0f);
	vec3 diffuse = diff * uLight.color;

	//specular
	vec3 viewDir = normalize(uCameraPos - vFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
	float specularStrength = 0.5;
	vec3 specular = spec * specularStrength * uLight.color;

	vec3 result = ambient + diffuse + specular;

	vec4 texColor = texture(baseColor, vUV);
	//FragColor = texColor * vec4(vColor, 1.0f);
	FragColor = texColor * vec4(result,1.0f);
}