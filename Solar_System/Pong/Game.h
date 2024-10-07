#pragma once
#include "Libs.h"
#include "Math.h"
#include "D3DApp.h"
#include "InputDevice.h"

class InputDevice;

class Game: public D3DApp
{
public:

	ULONGLONG prevTime = 0;
	ULONGLONG curTime = 0;
	float deltaTime = 0;

	Game();
	~Game();
	bool Initialize();
	void Run();
	void ProcessInput();
	void DestroyResources();
	void OnMouseMove(const InputDevice::MouseMoveEventArgs& args);

};
