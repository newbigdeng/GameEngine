#include "inputManager.h"

namespace eng
{
	void inputManager::SetKeyPressed(int key, bool pressed)
	{
		if (key < 0 || key >= static_cast<int>(m_keys.size()))return;

		m_keys[key] = pressed;
	}

	bool inputManager::IsKeyPressed(int key)
	{
		if (key < 0 || key >= static_cast<int>(m_keys.size()))return false;

		return m_keys[key];
	}
}