#include "Game.h"
#include <iostream>
#include "GLFW/glfw3.h"

bool Game::Init()
{
	std::string vertexShaderSource = R"(
		#version 330 core
		layout(location=0)in vec3 position;
		layout(location=1)in vec3 color;

		uniform vec2 uOffset;

		out vec3 vColor;
		void main()
		{
			vColor = color;
			gl_Position = vec4(position.x + uOffset.x,position.y + uOffset.y,position.z,1.0);
		}
	)";
	std::string fragmentShaderSource = R"(
		#version 330 core
		in vec3 vColor;
		out vec4 FragColor;
		
		uniform vec4 uColor;
		
		void main()
		{
			FragColor = vec4(vColor,1.0f)*uColor;
		}
	)";

	auto& graphicsAPI = eng::Engine::GetInstance().GetGraphicsAPI();
	auto shaderProgram = graphicsAPI.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

	return true;
}

void Game::Update(float deltaTime)
{
	std::cout << "Current Delta Time:" << deltaTime << std::endl;
	auto& input = eng::Engine::GetInstance().GetInputManager();
	if (input.IsKeyPressed(GLFW_KEY_W))
	{
		std::cout << "[W] is Pressed" << std::endl;
	}
}

void Game::Destory()
{
	std::cout << "´Ý»Ù" << std::endl;
}
