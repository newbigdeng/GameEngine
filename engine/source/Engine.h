#pragma once
#include <memory>
#include <chrono>

namespace eng 
{
    class Application;//向前声明

    class Engine
    {
    public:
        bool Init();
        void Run();
        void Destory();

        void SetApplication(Application* app);
        Application* GetApplication();
    private:
        std::unique_ptr<Application>m_application;
        std::chrono::steady_clock::time_point m_lastTimePoint;
    };
}
