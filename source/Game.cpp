#include "Game.h"
#include <iostream>

bool Game::Init()
{
	return true;
}

void Game::Update(float deltaTime)
{
	std::cout << "Current Delta Time:" << deltaTime << std::endl;
}

void Game::Destory()
{
	std::cout << "´Ý»Ù" << std::endl;
}
