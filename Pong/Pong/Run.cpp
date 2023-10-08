#include <Windows.h>
#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game game;
	game.Initialize();
	game.Run();
	
	game.DestroyResources();

	return 0;
}
