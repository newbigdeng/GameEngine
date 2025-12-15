#pragma once
#include <vector>
#include <string>
#include "scene\GameObject.h"
#include <memory>
#include "Common.h"

namespace eng
{
	class GameObject;
	class Scene
	{
	public:
		void Update(float deltaTime);
		void Clear();

		GameObject* CreateObject(const std::string& name, GameObject* parent = nullptr);

		template<typename T,typename = typename std::enable_if_t<std::is_base_of_v<GameObject,T>>>
		T* CreateObject(const std::string& name, GameObject* parent = nullptr)//用于创建子类
		{
			auto obj = new T();
			obj->SetName(name);
			obj->m_scene = this;
			SetParent(obj, parent);
			return obj;
		}

		bool SetParent(GameObject* obj, GameObject* parent);

		void SetMainCamera(GameObject* camera);
		GameObject* GetMainCamera();

		std::vector<LightData> CollectLights();
	private:
		void CollectLightsRecursive(GameObject* obj,std::vector<LightData>& out);
	private:
		std::vector<std::unique_ptr<GameObject>> m_objects;
		GameObject* m_mainCamera = nullptr;
	};
}