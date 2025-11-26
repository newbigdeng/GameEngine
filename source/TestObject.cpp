#include "TestObject.h"
#include <iostream>
#include "GLFW/glfw3.h"

TestObject::TestObject()
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
			FragColor = vec4(vColor,1.0f);
		}
	)";

	auto& graphicsAPI = eng::Engine::GetInstance().GetGraphicsAPI();
	auto shaderProgram = graphicsAPI.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
	m_material.SetShaderProgram(shaderProgram);


	std::vector<float>vertices{
		-0.5f,0.5f,0.0f,1.0f,0.0f,0.0f,
		-0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
		0.5f,0.5f,0.0f,0.0f,0.0f,1.0f,
		0.5f,-0.5f,0.0f,1.0f,0.0f,1.0f,
	};
	std::vector<unsigned int>indices{
		2,0,1,
		2,1,3
	};
	eng::VertexLayout layout;

	//Position
	layout.elements.push_back({ 0,3,GL_FLOAT,0 });
	//color
	layout.elements.push_back({ 1,3,GL_FLOAT,sizeof(float) * 3 });
	layout.stride = sizeof(float) * 6;

	m_mesh = std::make_shared<eng::Mesh>(layout, vertices, indices);
}

void TestObject::Update(float deltaTime)
{
	eng::GameObject::Update(deltaTime);
	std::cout << "Current Delta Time:" << deltaTime << std::endl;
	auto& input = eng::Engine::GetInstance().GetInputManager();
	if (input.IsKeyPressed(GLFW_KEY_W))
	{
		m_offsetY += 0.001f;
	}
	if (input.IsKeyPressed(GLFW_KEY_A))
	{
		m_offsetX -= 0.001f;
	}
	if (input.IsKeyPressed(GLFW_KEY_S))
	{
		m_offsetY -= 0.001f;
	}
	if (input.IsKeyPressed(GLFW_KEY_D))
	{
		m_offsetX += 0.001f;
	}
	m_material.SetParam("uOffset", m_offsetX, m_offsetY);



	eng::RenderCommand command;
	command.material = &m_material;
	command.mesh = m_mesh.get();

	auto& renderQueue = eng::Engine::GetInstance().GetRenderQueue();
	renderQueue.Submit(command);
}
