#pragma once
#include "scene\Component.h"


namespace eng
{
	class PlayerControllerCompnent :public Component
	{
		COMPONENT(PlayerControllerCompnent)
	public:
		void Update(float deltaTime)override;

	private:

		float m_sensitivity = 0.65f;
		float m_speed = 1.5f;

	};
}