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
	CircleComponent* ball{ nullptr };
	RectComponent* paddle1{ nullptr };
	RectComponent* paddle2{ nullptr };
	int score1 = 0;
	int score2 = 0;

	Game();
	~Game();
	bool Initialize();
	void Run();
	void DestroyResources();
};
