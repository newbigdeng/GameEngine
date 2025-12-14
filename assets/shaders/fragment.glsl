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

uniform sampler2D brick;
uniform sampler2D baseColor;
uniform vec4 uColor;

void main()
{
	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(uLight.position - vFragPos);

	float diff = max(dot(norm, lightDir),0.0f);
	vec3 diffuse = diff * uLight.color;

	vec4 texColor = texture(baseColor, vUV);
	//FragColor = texColor * vec4(vColor, 1.0f);
	FragColor = texColor * vec4(diffuse,1.0f);
}