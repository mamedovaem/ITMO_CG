#include <string>
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Initialize()
{
	//input = new InputDevice(this);

	paddle1 = new Paddle(this, 0.05F, 0.5F, {-0.9f, 0.f});
	components.push_back(paddle1);
	paddle2 = new Paddle(this, 0.05F, 0.5F, {0.9f, 0.f}, {1.0f, 1.0f, 0.0f, 1.0f});
	components.push_back(paddle2);

	ball = new Ball(this, 0.05F, { 0, 0 });
	components.push_back(ball);

	paddle1->matrixes.mMVP = DirectX::XMMatrixTranslation(paddle1->pos.x, paddle1->pos.y, 0); // * viewMatrix * projMatrix;
	paddle1->UpdateMatrixes();

	paddle2->matrixes.mMVP = DirectX::XMMatrixTranslation(paddle2->pos.x, paddle2->pos.y, 0);
	paddle2->UpdateMatrixes();

	prevTime = GetTickCount64();

	isResourcesAlloced = true;
	return true;
}

bool isExitRequested{ false };

void Game::SetScene()
{
	ball->pos = DirectX::XMFLOAT2{ 0.0f, 0.0f };
	paddle1->pos = DirectX::XMFLOAT2{ -0.9f, 0.0f };
	paddle2->pos = DirectX::XMFLOAT2{ 0.9f, 0.0f };

	ball->matrixes.mMVP = DirectX::XMMatrixTranslation(ball->pos.x, ball->pos.y, 0); // * viewMatrix * projMatrix;
	ball->UpdateMatrixes();

	paddle1->matrixes.mMVP = DirectX::XMMatrixTranslation(paddle1->pos.x, paddle1->pos.y, 0); // * viewMatrix * projMatrix;
	paddle1->UpdateMatrixes();

	paddle2->matrixes.mMVP = DirectX::XMMatrixTranslation(paddle2->pos.x, paddle2->pos.y, 0);
	paddle2->UpdateMatrixes();

	ball->velocityX = ball->initialVelocityX;
	ball->velocityY = ball->initialVelocityY;
}
void Game::Run()
{
	MSG msg = {};

	//float prevTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();

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

		//float curTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		curTime = GetTickCount64();
		
		deltaTime = (curTime - prevTime) * 1e-3f;

		ProcessInput();
		ball->Move(deltaTime);
		
		if (CheckCollision(paddle1))
		{
			DoCollision(paddle1);
		}
		if (CheckCollision(paddle2))
		{
			DoCollision(paddle2);
		}
		
		Render();

		prevTime = curTime + CheckOutOfBoundaries();
	}
}

void Game::ProcessInput()
{
	if (input->IsKeyDown(Keys::W))
	{
		paddle1->Move(true, deltaTime);
	}
	if (input->IsKeyDown(Keys::S))
	{
		paddle1->Move(false, deltaTime);
	}
	if (input->IsKeyDown(Keys::Up))
	{
		paddle2->Move(true, deltaTime);
	}
	if (input->IsKeyDown(Keys::Down))
	{
		paddle2->Move(false, deltaTime);
	}

}

bool Game::CheckCollision(Paddle* paddle)
{
	float delta_x{ 0 };
	if (ball->velocityX > 0) {
		delta_x = (paddle->pos.x - paddle->length) - (ball->pos.x + ball->radius);
	} else {
		delta_x = (ball->pos.x - ball->radius) - (paddle->pos.x + paddle->length);
	}
	bool collide_x = delta_x <= 0 && abs(ball->pos.x - paddle->pos.x) < ball->radius + paddle->length && paddle->pos.x * ball->velocityX > 0;

	float delta_y = abs(ball->pos.y - paddle->pos.y);
	bool collide_y = delta_y < paddle->width / 2;

	return collide_x && collide_y;
}

void Game::DoCollision(Paddle* paddle)
{
	float velocity = sqrt(ball->velocityX * ball->velocityX + ball->velocityY * ball->velocityY);
	ball->velocityX = -ball->velocityX;
	ball->velocityY = sin((ball->pos.y - paddle->pos.y) / (paddle->width / 2));
	float new_velocity = sqrt(ball->velocityX * ball->velocityX + ball->velocityY * ball->velocityY);
	ball->velocityX *= velocity / new_velocity * ball->multiplier;
	ball->velocityY *= velocity / new_velocity * ball->multiplier;

	return;
}

ULONGLONG Game::CheckOutOfBoundaries()
{
	if (ball->pos.x + ball->radius > 1.0f)
	{
		score1++;
	}
	else if (ball->pos.x - ball->radius < -1.0f)
	{
		score2++;
	}
	else {
		return 0;
	}
	std::string message =  std::to_string(score1) + " : " + std::to_string(score2);
	ULONGLONG start = GetTickCount64();
	MessageBoxA(hWnd, (LPCSTR) message.c_str(), "Score", MB_OK);
	SetScene();
	return (GetTickCount64() - start);
}

void Game::DestroyResources()
{
	if (input) 
	{
		delete input;
		input = nullptr;
	}

	if (paddle1) {
		paddle1->DestroyResources();
		delete paddle1;
		paddle1 = nullptr;
	}
	if (paddle2)
	{
		paddle2->DestroyResources();
		delete paddle2;
	}
	
	if (ball)
	{
		ball->DestroyResources();
		delete ball;
	}
}
