#include "GameObject.h"
#include <glm\gtc\matrix_transform.hpp>

namespace eng
{
	void GameObject::Update(float deltaTime)
	{
		for (auto& component : m_components)
		{
			component->Update(deltaTime);
		}

		for (auto it = m_children.begin(); it != m_children.end();)
		{
			if ((*it)->IsAlive())
			{
				(*it)->Update(deltaTime);
				++it;
			}
			else
			{
				it = m_children.erase(it);
			}
		}
	}
	const std::string GameObject::GetName() const
	{
		return m_name;
	}
	void GameObject::SetName(std::string name)
	{
		m_name = name;
	}

	GameObject* GameObject::GetParent()
	{
		return m_parent;
	}

	bool GameObject::IsAlive() const
	{
		return m_isAlive;
	}

	void GameObject::MarkForDestory()
	{
		m_isAlive = false;
	}

	void GameObject::AddComponent(Component* component)
	{
		m_components.emplace_back(component);
		component->m_owner = this;
	}


	glm::vec3 GameObject::GetWorldPosition() const
	{
		glm::vec4 hom = GetWorldTransform() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return glm::vec3(hom) / hom.w;
	}

	const glm::vec3& GameObject::GetPosition() const
	{
		return m_position;
	}

	void GameObject::SetPosition(glm::vec3& pos)
	{
		m_position = pos;
	}

	const glm::quat& GameObject::GetRotation() const
	{
		return m_rotation;
	}

	void GameObject::SetRotation(glm::quat& rot)
	{
		m_rotation = rot;
	}

	const glm::vec3& GameObject::GetScale() const
	{
		return m_scale;
	}

	void GameObject::SetScale(glm::vec3& sca)
	{
		m_scale = sca;
	}

	glm::mat4 GameObject::GetLocalTransform() const
	{
		glm::mat4 mat = glm::mat4(1.0f);
		//translate
		mat = glm::translate(mat, m_position);

		//rotation
		//mat = glm::rotate(mat, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		//mat = glm::rotate(mat, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		//mat = glm::rotate(mat, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		mat = mat * glm::mat4_cast(m_rotation);

		//scale
		mat = glm::scale(mat, m_scale);

		return mat;
	}

	glm::mat4 GameObject::GetWorldTransform() const
	{
		if (m_parent)
		{
			return m_parent->GetWorldTransform() * GetLocalTransform();
		}
		else
		{
			return GetLocalTransform();
		}
	}

}