#pragma once
#include "eng.h"
#include <memory>

class Game :public eng::Application
{
public:
	bool Init() override;
	void Update(float deltaTime)override;
	void Destory() override;

private:
	eng::Material m_Material;
	std::unique_ptr<eng::Mesh> m_mesh;
	float offset_X = 0.f;
	float offset_Y = 0.f;
};