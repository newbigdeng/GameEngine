#pragma once
#include <string>
#include <vector>
#include <memory>

namespace eng
{
	class GameObject
	{
	public:
		virtual ~GameObject() = default;
		virtual void Update(float deltaTime);
		const std::string GetName() const;
		void SetName(std::string name);
		GameObject* GetParent();
		bool IsAlive() const;
		void MarkForDestory();
	protected:
		GameObject() = default;
	private:
		std::string m_name;
		GameObject* m_parent = nullptr;
		std::vector<std::unique_ptr<GameObject>>m_children;
		bool m_isAlive = true;

		friend class Scene;
	};
}