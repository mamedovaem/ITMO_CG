#include "Game.h"

Game::Game()
{
	

}
Game::~Game()
{
	//DestroyResources();
}
bool Game::Initialize()
{

	ball = new CircleComponent(this, 0.05F, {0.0F, 0.0F, 1.0F, 1.0F});
	components.push_back(ball);

	paddle1 = new RectComponent(this, 0.05F,  0.4F, {-0.8F, 0.0F, 1.0F, 1.0F});
	components.push_back(paddle1);
	paddle2 = new RectComponent(this, 0.05F, 0.4F, { 0.8F, 0.0F, 1.0F, 1.0F });
	components.push_back(paddle2);

	isResourcesAlloced = true;
	return true;
}

void Game::Run()
{
	


	MSG msg = {};
	bool isExitRequested = false;
	while (!isExitRequested) 
	{
		// Handle the windows messages.
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT) 
		{
			isExitRequested = true;
		}	

		
		static float t = 0.0f;

			t += (float)DirectX::XM_PI * 10.125f;
			DirectX::XMMATRIX mOrbit = DirectX::XMMatrixRotationY(-t);

			// Матрица-спин: вращение объекта вокруг своей оси

			DirectX::XMMATRIX mSpin = DirectX::XMMatrixRotationX(t * 2);

			// Матрица-позиция: перемещение на три единицы влево от начала координат

			DirectX::XMMATRIX mTranslate = DirectX::XMMatrixTranslation(t, 0.0f, 0.0f);

			// Матрица-масштаб: сжатие объекта в 2 раза

			DirectX::XMMATRIX mScale = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
			paddle1->matrixes.mProjection = mScale * mSpin * mTranslate * mOrbit;
			paddle1->UpdateMatrixes();


		Render();
	}

	DestroyResources();
}

void Game::DestroyResources()
{
	delete paddle1;
	delete paddle2;
	delete ball;

}
