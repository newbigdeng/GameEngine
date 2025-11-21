#pragma once
#include <array>

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
	private:
		std::array<bool, 256> m_keys = { false };
		friend class Engine;
	};
}