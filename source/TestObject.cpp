#include "TestObject.h"
#include <iostream>
#include "GLFW/glfw3.h"

TestObject::TestObject()
{
	std::string vertexShaderSource = R"(
		#version 330 core
		layout(location=0)in vec3 position;
		layout(location=1)in vec3 color;

		uniform mat4 uModel;

		out vec3 vColor;
		void main()
		{
			vColor = color;
			gl_Position = uModel * vec4(position,1.0);
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

	auto position = GetPosition();
	auto& input = eng::Engine::GetInstance().GetInputManager();
	if (input.IsKeyPressed(GLFW_KEY_W))
	{
		position.y += 0.001f;
	}
	if (input.IsKeyPressed(GLFW_KEY_A))
	{
		position.x -= 0.001f;
	}
	if (input.IsKeyPressed(GLFW_KEY_S))
	{
		position.y -= 0.001f;
	}
	if (input.IsKeyPressed(GLFW_KEY_D))
	{
		position.x += 0.001f;
	}
	SetPosition(position);


	eng::RenderCommand command;
	command.material = &m_material;
	command.mesh = m_mesh.get();
	command.modelMatrix = GetWorldTransform();

	auto& renderQueue = eng::Engine::GetInstance().GetRenderQueue();
	renderQueue.Submit(command);
}
