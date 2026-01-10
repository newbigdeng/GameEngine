#include "Engine.h"
#include "Application.h"
#include "scene\Component.h"
#include "scene\GameObject.h"
#include "scene\components\CameraComponent.h"
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

	void MouseButtomCallBack(GLFWwindow* window, int buttom, int action, int mods)
	{
		auto& inputManager = eng::Engine::GetInstance().GetInputManager();
		if (action == GLFW_PRESS)
		{
			inputManager.SetMouseButtonPressed(buttom, true);
		}
		else if (action == GLFW_RELEASE)
		{
			inputManager.SetMouseButtonPressed(buttom, false);
		}
	}
	void CurosrPositionCallBack(GLFWwindow* window, double xpos, double ypos)
	{
		auto& inputManager = eng::Engine::GetInstance().GetInputManager();
		inputManager.SetMousePositionOld(inputManager.GetMousePositionCurrent());

		glm::vec2 currentPos(static_cast<float>(xpos), static_cast<float>(ypos));
		inputManager.SetMousePositionCurrent(currentPos);
	}

	Engine& Engine::GetInstance()
	{
		static Engine instance;
		return instance;
	}

	bool Engine::Init(int width, int height)
	{
		IsDebug = false;
		if (!m_application)
		{
			return false;
		}

		if (!glfwInit())
		{
			return false;
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
			return false;
		}
		glfwMakeContextCurrent(m_window);

		glfwSetKeyCallback(m_window,KeyCallback);//按键回调
		glfwSetMouseButtonCallback(m_window, MouseButtomCallBack);
		glfwSetCursorPosCallback(m_window, CurosrPositionCallBack);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			return false;

		if(!m_graphicsAPI.Init())return false;
		//if (IsDebug)
		//{
			//m_imgui = std::make_unique<MyImGui>(m_window, "#version 330 core");
			//if (!m_imgui->Init())return false;
		//}
		return true;
		
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
			glfwPollEvents();//处理输入事件
			
			auto now = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
			m_lastTimePoint = now;
			//处理imgui事件
			if (IsDebug)
			{
				//m_imgui->Update(deltaTime);
			}

			m_application->Update(deltaTime);

			m_graphicsAPI.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_graphicsAPI.ClearBuffers();

			CameraData cameraData;
			std::vector<LightData> lights;

			int width = 0, height = 0;
			glfwGetWindowSize(m_window, &width, &height);
			float aspect = static_cast<float>(width) / static_cast<float>(height);
			if (m_currentScene)
			{
				if (auto cameraObject = m_currentScene->GetMainCamera())
				{
					//获取矩阵数据
					auto cameraComponent = cameraObject->GetComponent<CameraComponent>();
					if (cameraComponent)
					{
						cameraData.viewMatrix = cameraComponent->GetViewMatrix();
						cameraData.projectionMatrix = cameraComponent->GetProjectionMatrix(aspect);
						cameraData.position = cameraObject->GetWorldPosition();
					}
				}

				lights = m_currentScene->CollectLights();//获取场景里的灯光数据
			}

			m_renderQueue.Draw(m_graphicsAPI,cameraData,lights);

			//进行imgui渲染
			if (IsDebug)
			{
				//m_imgui->Render();
			}

			glfwSwapBuffers(m_window);

			m_inputManager.SetMousePositionOld(m_inputManager.GetMousePositionCurrent());

		}
	}
	void Engine::Destory()
	{
		if (IsDebug)
		{
			//if (m_imgui)
			//{
				//销毁ImGui
				//m_imgui->Close();
				//m_imgui.reset();
			//}
		}
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
	FileSystem& Engine::GetFileSystem()
	{
		return m_fileSystem;
	}
	TextureManager& Engine::GetTextureManager()
	{
		return m_textureManager;
	}
	void Engine::SetScene(Scene* scene)
	{
		m_currentScene.reset(scene);
	}
	Scene* Engine::GetScene()
	{
		return m_currentScene.get();
	}
}
