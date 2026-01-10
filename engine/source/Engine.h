#pragma once
#include <memory>
#include <chrono>
#include "input\inputManager.h"
#include "graphics\GraphicsAPI.h"
#include "graphics\Texture.h"
#include "render\RenderQueue.h"
#include "scene\Scene.h"
#include "io\FileSystem.h"
#include "gui\Gui.h"

struct GLFWwindow;

namespace eng 
{
    class Application;//向前声明
    
    class Engine
    {
    public:
        static Engine& GetInstance();
    private:
        Engine() = default;
        Engine(const Engine&) = delete;
        Engine(Engine&&) = delete;
        Engine& operator=(const Engine&) = delete;
        Engine& operator=(Engine&&) = delete;
    public:
        bool Init(int width,int height);
        void Run();
        void Destory();

        void SetApplication(Application* app);
        Application* GetApplication();
        inputManager& GetInputManager();
        GraphicsAPI& GetGraphicsAPI();
        RenderQueue& GetRenderQueue();
        FileSystem& GetFileSystem();
        TextureManager& GetTextureManager();
        MyImGui* GetGui();

        void SetScene(Scene* scene);
        Scene* GetScene();
    private:
        std::unique_ptr<Application>m_application;
        std::chrono::steady_clock::time_point m_lastTimePoint;
        GLFWwindow* m_window = nullptr;
        inputManager m_inputManager;
        GraphicsAPI m_graphicsAPI;
        TextureManager m_textureManager;
        RenderQueue m_renderQueue;
        FileSystem m_fileSystem;
        std::unique_ptr<Scene>m_currentScene;

        std::unique_ptr<MyImGui> m_gui;
    };
}
