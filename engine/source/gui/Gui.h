#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace eng
{
	class MyImGui
	{
	public:
		MyImGui(GLFWwindow* win, const char* ver);
		bool Init();
		void Update(float deltaTime);
		void Render();
		void Close();


	private:
		GLFWwindow* window;
		const char* glsl_version;
		bool enabled = true;

		void DrawEngineDebugPanel();
	};
}