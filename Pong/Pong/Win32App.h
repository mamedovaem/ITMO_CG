#pragma once
#include "Libs.h"
#include "InputDevice.h"

class InputDevice;

class Win32App
{

public:
LPCWSTR applicationName;
HINSTANCE hInstance;
HWND hWnd;
WNDCLASSEX wc;

InputDevice* input;

int ClientWidth;
int ClientHeight;
	bool isInitialized = false;

	Win32App();
	bool Initialize();
	~Win32App()
	{
		delete input;
	}
};