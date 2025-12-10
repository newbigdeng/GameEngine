#version 330 core
in vec3 vColor;
in vec2 vUV;
out vec4 FragColor;

uniform sampler2D brick;
uniform vec4 uColor;

void main()
{
	vec4 texColor = texture(brick, vUV);
	FragColor = texColor * vec4(vColor, 1.0f);
}