#include "Component.h"

namespace eng
{
	 size_t Component::nextId = 1;
	 void Component::Init()
	 {

	 }
	void Component::Update(float deltaTime)
	{

	}
	GameObject* Component::GetOwner()
	{
		return m_owner;
	}
}