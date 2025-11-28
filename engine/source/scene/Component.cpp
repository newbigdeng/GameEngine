#include "Component.h"

namespace eng
{
	void Component::Update(float deltaTime)
	{

	}
	GameObject* Component::GetOwner()
	{
		return m_owner;
	}
}