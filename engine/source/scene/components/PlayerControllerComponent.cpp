#include "PlayerControllerComponent.h"
#include "input\inputManager.h"
#include "Engine.h"
#include "GLFW\glfw3.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\vec4.hpp>


namespace eng
{
	void PlayerControllerCompnent::Update(float deltaTime)
	{
		auto& inputManager = Engine::GetInstance().GetInputManager();

		auto rotation = m_owner->GetRotation();
		if (inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			const auto& oldPos = inputManager.GetMousePositionOld();
			const auto& currentPos = inputManager.GetMousePositionCurrent();

			auto deltaX = currentPos.x - oldPos.x;
			auto deltaY = currentPos.y - oldPos.y;

			float yAngle = -deltaX * m_sensitivity * deltaTime;
			float xAngle = -deltaY * m_sensitivity * deltaTime;

			glm::quat yRot = glm::angleAxis(yAngle, glm::vec3(0.0f, 1.0f, 0.0f));//½Ç¶È£¬Ðý×ªÖá
			glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
			glm::quat xRot = glm::angleAxis(xAngle, right);

			glm::quat deltaRot = yRot * xRot;
			rotation = glm::normalize(deltaRot * rotation);
			//rotation.y -= deltaX * m_sensitivity * deltaTime;
			//rotation.x -= deltaY * m_sensitivity * deltaTime;
			m_owner->SetRotation(rotation);
		}

		//glm::mat4 rotMat(1.0f);
		//rotMat = glm::rotate(rotMat, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		//rotMat = glm::rotate(rotMat, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		//rotMat = glm::rotate(rotMat, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		glm::vec3 front = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
		//glm::vec3 front = glm::normalize(glm::vec3(rotMat * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
		//glm::vec3 right = glm::normalize(glm::vec3(rotMat * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));

		auto position = m_owner->GetPosition();
		if (inputManager.IsKeyPressed(GLFW_KEY_W))
		{
			position += front * m_speed * deltaTime;
		}
		if (inputManager.IsKeyPressed(GLFW_KEY_A))
		{
			position -= right * m_speed * deltaTime;
		}
		if (inputManager.IsKeyPressed(GLFW_KEY_S))
		{
			position -= front * m_speed * deltaTime;
		}
		if (inputManager.IsKeyPressed(GLFW_KEY_D))
		{
			position += right * m_speed * deltaTime;
		}
		m_owner->SetPosition(position);
	}
}