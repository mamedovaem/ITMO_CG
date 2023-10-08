#include "Game.h"

int main()
{
	Game game;
	game.Initialize();
	game.Run();
	
	game.DestroyResources();


		return 0;
}