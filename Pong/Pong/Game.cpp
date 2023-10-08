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

	paddle1 = new Paddle(this, 0.05F, 0.5F, true, {0, 0, 0, 1});
	components.push_back(paddle1);
	paddle2 = new Paddle(this, 0.05F, 0.5F, false, {0, 0, 0, 1});
	components.push_back(paddle2);

	ball = new Ball(this, 0.05F, { 0, 0, 0, 1 });
	components.push_back(ball);

	paddle1->center.x -= 0.9f;

	DirectX::XMMATRIX mTranslate;

	mTranslate = DirectX::XMMatrixTranslation(-0.9f, 0.0f, 0.0f);
	paddle1->matrixes.mMVP = mTranslate; // * viewMatrix * projMatrix;
	paddle1->UpdateMatrixes();

	paddle2->center.x += 0.9f;

	mTranslate = DirectX::XMMatrixTranslation(0.9f, 0.0f, 0.0f);
	paddle2->matrixes.mMVP = mTranslate;
	paddle2->UpdateMatrixes();

	 prevTime = GetTickCount64();

	isResourcesAlloced = true;
	return true;
}

bool isExitRequested{ false };
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
		
		deltaTime += (curTime - prevTime) * 1e-3f;

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

		prevTime = curTime;
	}
}

void Game::ProcessInput()
{
	if (input->IsKeyDown(Keys::W))
	{
		paddle1->Move(true);
	}
	if (input->IsKeyDown(Keys::S))
	{
		paddle1->Move(false);
	}
	if (input->IsKeyDown(Keys::Up))
	{
		paddle2->Move(true);
	}
	if (input->IsKeyDown(Keys::Down))
	{
		paddle2->Move(false);
	}

}

bool Game::CheckCollision(Paddle* paddle)
{
	float differenceX = ball->center.x - paddle->center.x;
	float differenceY = ball->center.y - paddle->center.y;


	float clampX = max( - paddle->length / 2.0f, min((paddle->length / 2.0f), differenceX));
	float clampY = max((-paddle->width / 2.0f), min((paddle->width / 2.0f), differenceY));

	float closestX = paddle->center.x + clampX;
	float closestY = paddle->center.y + clampY;

	differenceX = closestX - ball->center.x;
	differenceY = closestY - ball->center.y;

	float length = sqrtf(powf(differenceX, 2) + powf(differenceY, 2));

	return (length < ball->radius);

}

void Game::DoCollision(Paddle* paddle)
{
	float oldVelocityX = ball->velocityX;
	float oldVelocityY = ball->velocityY;

	float distanceY = ball->center.y - paddle->center.y;
	float percentage = distanceY / paddle->width * 2;

	float multiplier = 1.0f;

	//ball->velocityY = 0;

	float velocityLength = sqrtf(powf(ball->velocityX, 2) + powf(ball->velocityY, 2));
	float oldVelocityLength = sqrtf(powf(oldVelocityX, 2) + powf(oldVelocityY, 2));

	if (paddle->isLeft)
	{
		ball->velocityX = 1.0f * abs(ball->velocityX);
	}
	else
	{
		ball->velocityX = -1.0f * abs(ball->velocityX);
	}

	ball->velocityY =  oldVelocityY * percentage * multiplier;

	ball->velocityX = ball->velocityX / velocityLength * oldVelocityLength;
	ball->velocityY = ball->velocityY / velocityLength * oldVelocityLength;

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
