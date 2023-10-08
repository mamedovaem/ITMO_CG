#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Initialize()
{
	paddle1 = new RectComponent(this, 0.05F, 0.4F, {0, 0, 0, 1});
	components.push_back(paddle1);
	paddle2 = new RectComponent(this, 0.05F, 0.4F, {0, 0, 0, 1});
	components.push_back(paddle2);

	ball = new CircleComponent(this, 0.05F, { 0, 0, 0, 1 });
	components.push_back(ball);

	isResourcesAlloced = true;
	return true;
}

bool isExitRequested{ false };
void Game::Run()
{
	MSG msg = {};

	float prevTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
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

		float curTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		float delta = curTime - prevTime;
		DirectX::XMMATRIX mTranslate;

		const float timeScale = 1e-18f;
		mTranslate = DirectX::XMMatrixTranslation(-0.9f, sin(curTime * delta * timeScale), 0.0f);
		paddle1->matrixes.mMVP = mTranslate; // * viewMatrix * projMatrix;
		paddle1->UpdateMatrixes();

		mTranslate = DirectX::XMMatrixTranslation(0.9f, cos(curTime * delta * timeScale), 0.0f);
		paddle2->matrixes.mMVP = mTranslate;
		paddle2->UpdateMatrixes();

		mTranslate = DirectX::XMMatrixTranslation(sin(curTime * delta * timeScale), cos(curTime * delta * timeScale), 0.0f);
		ball->matrixes.mMVP = mTranslate;
		ball->UpdateMatrixes();

		Render();

		prevTime = curTime;
	}
}

void Game::DestroyResources()
{
	if (paddle1) {
		paddle1->DestroyResources();
		delete paddle1;
		paddle1 = nullptr;
	}
	paddle2->DestroyResources();
	delete paddle2;
	ball->DestroyResources();
	delete ball;
}
