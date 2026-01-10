
#include "MyImGui.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace eng
{
	MyImGui::MyImGui(GLFWwindow* win, const char* ver) : window(win), glsl_version(ver) {
		assert(win != nullptr && "GLFW window is null!");
		assert(ver != nullptr && "GLSL version is null!");
	}
	MyImGui::~MyImGui()
	{
		Close();
	}
	bool MyImGui::Init()
	{
		IMGUI_CHECKVERSION();

		ImGuiContext* ctx = ImGui::CreateContext();
		if (!ctx) return false; // 检查Context创建

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // 键盘导航
		ImGui::StyleColorsDark(); // 深色调试风格
		// 绑定引擎的GLFW窗口+OpenGL上下文（和引擎渲染环境强绑定）
		// 检查GLFW/OpenGL绑定是否成功
		if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
			ImGui::DestroyContext(ctx);
			return false;
		}
		if (!ImGui_ImplOpenGL3_Init(glsl_version)) {
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext(ctx);
			return false;
		}
		return true;
	}
	void MyImGui::Update(float deltaTime)
	{
		if (enabled)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			// 在这里写【引擎调试面板】的ImGui逻辑，比如帧率监控、引擎配置面板
			DrawEngineDebugPanel();
		}
	}
	void MyImGui::Render()
	{
		if (enabled)
		{
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
	}
	void MyImGui::Close()
	{
		if (enabled)
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}
	}
	void MyImGui::DrawEngineDebugPanel()
	{
		ImGui::Begin("🔧 我的游戏引擎 - 调试面板");
		{
			ImGui::Text("引擎状态：运行中");
			ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
			ImGui::Separator();

			// 引擎配置项：实时修改，立即生效
			static float clearColor[3] = { 0.1f, 0.1f, 0.15f };
			ImGui::ColorEdit3("背景色", clearColor);
			glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.0f);

			// 场景调试：比如显示场景物体数量
			ImGui::Text("场景物体数量：%d", 100); // 替换成你的场景实际数量

			// 调试开关
			ImGui::Checkbox("启用ImGui", &enabled);
			//ImGui::Checkbox("显示碰撞框", &Renderer::showColliders); // 渲染子系统的调试开关
		}
		ImGui::End();

		// 可以加更多调试面板：比如控制台、性能分析、属性检查器等
		ImGui::Begin("📊 性能监控");
		ImGui::Text("CPU占用: %.2f%%", 15.6f);
		ImGui::Text("内存占用: %.2f MB", 64.5f);
		ImGui::End();
	}
}