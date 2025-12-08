#pragma once
#include <array>
#include <glm\vec2.hpp>

namespace eng
{
	class inputManager
	{
	private:
		inputManager() = default;
		inputManager(const inputManager&) = delete;
		inputManager(inputManager&&) = delete;
		inputManager& operator=(const inputManager&) = delete;
		inputManager& operator=(inputManager&&) = delete;
	public:
		void SetKeyPressed(int key, bool pressed);
		bool IsKeyPressed(int key);

		void SetMouseButtonPressed(int buttom,bool pressed);
		bool IsMouseButtonPressed(int buttom);

		void SetMousePositionOld(const glm::vec2& pos);
		const glm::vec2 GetMousePositionOld() const;

		void SetMousePositionCurrent(const glm::vec2& pos);
		const glm::vec2 GetMousePositionCurrent() const;
	private:
		std::array<bool, 256> m_keys = { false };
		std::array<bool, 16> m_mouseKeys = { false };
		glm::vec2 m_mousePositionOld = glm::vec2(0.0f);
		glm::vec2 m_mousePositionCurrent = glm::vec2(0.0f);

		friend class Engine;
	};
}