#pragma once
#include "Libs.h"
#include "Math.h"
#include "D3DApp.h"
#include "InputDevice.h"
#include "TriangleComponent.h"
#include "Ball.h"
#include "Paddle.h"

class InputDevice;

class Game: public D3DApp
{
public:
//	Win32App win32App;

	//InputDevice* input { nullptr };
	
	Ball* ball { nullptr };
	Paddle* paddle1 { nullptr };
	Paddle* paddle2 { nullptr };

	ULONGLONG prevTime = 0;
	ULONGLONG curTime = 0;
	float deltaTime = 0;

	int score1 = 0;
	int score2 = 0;

	Game();
	~Game();
	bool Initialize();
	void Run();
	void ProcessInput();
	bool CheckCollision(Paddle* paddle);
	void DoCollision(Paddle* paddle);
	void DestroyResources();

};
