#include "Engine.h"
#include "Application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace eng
{
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int modes)
	{
		auto& inputManager = eng::Engine::GetInstance().GetInputManager();
		if (action == GLFW_PRESS)
		{
			inputManager.SetKeyPressed(key, true);
		}
		else if (action == GLFW_RELEASE)
		{
			inputManager.SetKeyPressed(key, false);
		}
	}
	Engine& Engine::GetInstance()
	{
		static Engine instance;
		return instance;
	}

	bool Engine::Init(int width, int height)
	{
		if (!m_application)
		{
			return false;
		}

		if (!glfwInit())
		{
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		m_window = glfwCreateWindow(width, height, "GameEngine", nullptr, nullptr);
		if (!m_window)
		{
			std::cout << "Fail To Create Window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(m_window);
		glfwSetKeyCallback(m_window,KeyCallback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			return -1;


		return m_application->Init();
	}

	void Engine::Run()
	{
		if (!m_application)
		{
			return;
		}

		m_lastTimePoint = std::chrono::high_resolution_clock::now();
		while (!glfwWindowShouldClose(m_window)&&!m_application->NeedsToBeClosed())
		{
			glfwPollEvents();//处理事件


			auto now = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
			m_lastTimePoint = now;

			m_application->Update(deltaTime);

			m_graphicsAPI.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_graphicsAPI.ClearBuffers();

			m_renderQueue.Draw(m_graphicsAPI);

			glfwSwapBuffers(m_window);
		}
	}
	void Engine::Destory()
	{
		if (m_application)
		{
			m_application->Destory();
			m_application.reset();
			m_window = nullptr;
		}
	}
	void Engine::SetApplication(Application* app)
	{
		m_application.reset(app);
	}
	Application* Engine::GetApplication()
	{
		return m_application.get();
	}
	inputManager& Engine::GetInputManager()
	{
		return m_inputManager;
	}
	GraphicsAPI& Engine::GetGraphicsAPI()
	{
		return m_graphicsAPI;
	}
	RenderQueue& Engine::GetRenderQueue()
	{
		return m_renderQueue;
	}
}
