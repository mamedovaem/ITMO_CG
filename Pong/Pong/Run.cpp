#pragma once
#include "Run.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	

	game.Initialize();
	game.Run();
	
	game.DestroyResources();

	return 0;
}
