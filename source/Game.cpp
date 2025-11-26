#include "Game.h"
#include "TestObject.h"
#include <iostream>

bool Game::Init()
{
	m_scene.CreateObject<TestObject>("TestObject");

	return true;
}

void Game::Update(float deltaTime)
{
	m_scene.Update(deltaTime);
}

void Game::Destory()
{
	std::cout << "´Ý»Ù" << std::endl;
}
