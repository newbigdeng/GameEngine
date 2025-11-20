#include "Game.h"


int main()
{
	Game* game = new Game();
	eng::Engine engine;
	engine.SetApplication(game);

	if (engine.Init(1280,960))
	{
		engine.Run();
	}

	engine.Destory();
	return 0;
}