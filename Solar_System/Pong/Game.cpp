#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Initialize()
{
	Sun = new SphereComponent(this, 0.3f, { 1.0f, 1.0f, 0, 1.0f });
	components.push_back(Sun);

	prevTime = GetTickCount64();

	isResourcesAlloced = true;
	return true;
}

bool isExitRequested{ false };
void Game::Run()
{
	MSG msg = {};

	while (!isExitRequested)
	{
		// Handle the windows messages.
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT) {
			isExitRequested = true;
		}

		curTime = GetTickCount64();
		
		deltaTime += (curTime - prevTime) * 1e-3f;

		ProcessInput();
		Render();

		prevTime = curTime;
	}
}

void Game::ProcessInput()
{
	if (input->IsKeyDown(Keys::W))
	{
	
	}
	if (input->IsKeyDown(Keys::S))
	{
	
	}
	if (input->IsKeyDown(Keys::Up))
	{
	
	}
	if (input->IsKeyDown(Keys::Down))
	{
	
	}

}

void Game::DestroyResources()
{
	if (input)
	{
		delete input;
		input = nullptr;
	}

	if (Sun) {
		Sun->DestroyResources();
		delete Sun;
		Sun = nullptr;
	}

}