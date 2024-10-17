#include "Game.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game* game = new Game();

	game->Initialize();
	game->Run();

	game->DestroyResources();

	return 0;
}
