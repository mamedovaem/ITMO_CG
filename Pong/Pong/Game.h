#pragma once
#include "Libs.h"
#include "D3DApp.h"
#include "TriangleComponent.h"
#include "CircleComponent.h"
#include "RectComponent.h"

class Game: public D3DApp
{
public:
//	Win32App win32App;
	CircleComponent* ball;
	RectComponent* paddle1;
	RectComponent* paddle2;
	int score1 = 0;
	int score2 = 0;

	Game();
	~Game();
	bool Initialize();
	void Run();
	void DestroyResources();
};
