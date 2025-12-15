#include "Scene.h"
#include "components\LightComponent.h"

namespace eng
{
	void Scene::Update(float deltaTime)
	{
		for (auto it = m_objects.begin(); it != m_objects.end();)
		{
			if ((*it)->IsAlive())
			{
				(*it)->Update(deltaTime);
				++it;
			}
			else
			{
				it = m_objects.erase(it);
			}
		}
	}

	void Scene::Clear()
	{
		m_objects.clear();
	}

	bool Scene::SetParent(GameObject* obj, GameObject* parent)
	{
		bool result = false;
		auto currentParent = obj->GetParent();
		if (parent == nullptr)//把物体移到根场景下
		{
			if (currentParent != nullptr)//若对象有父类
			{
				auto it = std::find_if(
					currentParent->m_children.begin(),
					currentParent->m_children.end(),
					[obj](const std::unique_ptr<GameObject>& el)
					{
						return el.get() == obj;
					}
				);//在父类中找到这个子类
				if (it != currentParent->m_children.end())
				{
					m_objects.push_back(std::move(*it));
					(*it)->m_parent = nullptr;
					currentParent->m_children.erase(it);
					result = true;
				}
			}
			else//对象没有父类:刚创建的物体或者是在根场景下的物体
			{
				auto it = std::find_if(
					m_objects.begin(),
					m_objects.end(),
					[obj](const std::unique_ptr<GameObject>& el)
					{
						return el.get() == obj;
					}
				);
				if (it == m_objects.end())//刚创建
				{
					std::unique_ptr<GameObject> objHolder(obj);
					m_objects.push_back(std::move(objHolder));
					result = true;
				}
			}
		}
		else//要移动到非根场景下面
		{
			if (currentParent != nullptr)
			{
				auto it = std::find_if(
					currentParent->m_children.begin(),
					currentParent->m_children.end(),
					[obj](const std::unique_ptr<GameObject>& el)
					{
						return el.get() == obj;
					}
				);//在父类中找到这个子类
				if (it != currentParent->m_children.end())
				{
					bool found = false;//父类不能变成子类的子类
					auto currentElement = parent;
					while (currentElement)
					{
						if (currentElement->m_parent == obj)
						{
							found = true;
							break;
						}
						currentElement = currentElement->GetParent();
					}
					if (!found)
					{
						parent->m_children.push_back(std::move(*it));
						(*it)->m_parent = parent;
						currentParent->m_children.erase(it);
						result = true;
					}
				}
			}
			else//把根场景下的物体移到别的地方去
			{
				auto it = std::find_if(
					m_objects.begin(),
					m_objects.end(),
					[obj](const std::unique_ptr<GameObject>& el)
					{
						return el.get() == obj;
					}
				);
				if (it == m_objects.end())//刚创建
				{
					std::unique_ptr<GameObject> objHolder(obj);
					parent->m_children.push_back(std::move(objHolder));
					obj->m_parent = parent;
					result = true;
				}
				else
				{
					bool found = false;//父类不能变成子类的子类
					auto currentElement = parent;
					while (currentElement)
					{
						if (currentElement->m_parent == obj)
						{
							found = true;
							break;
						}
						currentElement = currentElement->GetParent();
					}
					if (!found)
					{
						parent->m_children.push_back(std::move(*it));
						obj->m_parent = parent;
						m_objects.erase(it);
						result = true;
					}
				}

			}
		}
		return result;
	}

	void Scene::SetMainCamera(GameObject* camera)
	{
		m_mainCamera = camera;
	}

	GameObject* Scene::GetMainCamera()
	{
		return m_mainCamera;
	}

	std::vector<LightData> Scene::CollectLights()
	{
		std::vector<LightData> lights;
		for (auto& obj : m_objects)
		{
			CollectLightsRecursive(obj.get(), lights);
		}
		return lights;
	}

	void Scene::CollectLightsRecursive(GameObject* obj, std::vector<LightData>& out)
	{
		if (auto light = obj->GetComponent<LightComponent>())
		{
			LightData data;
			data.color = light->GetColor();
			data.position = obj->GetWorldPosition();
			out.push_back(data);
		}

		for (auto& child : obj->m_children)
		{
			CollectLightsRecursive(child.get(), out);//递归获取子对象
		}
	}

	GameObject* Scene::CreateObject(const std::string& name, GameObject* parent)
	{
		auto obj = new GameObject();
		obj->SetName(name);
		obj->m_scene = this;
		SetParent(obj, parent);
		return obj;
	}
}