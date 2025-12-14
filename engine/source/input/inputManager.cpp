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

	void inputManager::SetMouseButtonPressed(int buttom, bool pressed)
	{
		if (buttom < 0 || buttom >= static_cast<int>(m_mouseKeys.size()))return;

		m_mouseKeys[buttom] = pressed;
	}
	bool inputManager::IsMouseButtonPressed(int buttom)
	{
		if (buttom < 0 || buttom >= static_cast<int>(m_mouseKeys.size()))return false;

		return m_mouseKeys[buttom];
	}

	void inputManager::SetMousePositionOld(const glm::vec2& pos)
	{
		m_mousePositionOld = pos;
	}
	const glm::vec2 inputManager::GetMousePositionOld() const
	{
		return m_mousePositionOld;
	}

	void inputManager::SetMousePositionCurrent(const glm::vec2& pos)
	{
		m_mousePositionCurrent = pos;
	}
	const glm::vec2 inputManager::GetMousePositionCurrent() const
	{
		return m_mousePositionCurrent;
	}
}