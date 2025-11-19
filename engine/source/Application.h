#pragma once

namespace eng
{
    class Application
    {
    public:
        virtual bool Init() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Destory() = 0;

        bool SetNeedsToBeClosed(bool value);
        bool NeedsToBeClosed() const;
    private:
        bool m_needsToBeClosed = false;

    };
}
