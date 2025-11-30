#pragma once

namespace eng
{
	class GameObject;
	class Component
	{
	public:
		virtual ~Component() = default;
		virtual void Update(float deltaTime);
		virtual size_t GetTypeId() const = 0;

		GameObject* GetOwner();

		template<typename T>
		static size_t StaticTypeId()
		{
			//静态变量，对同一个T只初始化一次
			static size_t TypeId = nextId++;
			return TypeId;
		}

	protected:
		GameObject* m_owner = nullptr;

		friend class GameObject;
	private:
		static size_t nextId;//标识符
	};

#define COMPONENT(ComponentClass)\
public:\
	static size_t TypeId() {return Component::StaticTypeId<ComponentClass>();}\
	size_t GetTypeId() const override {return TypeId();}
}
