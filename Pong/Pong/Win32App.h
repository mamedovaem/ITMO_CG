#pragma once
#include "Libs.h"


class Win32App
{

public:
LPCWSTR applicationName;
HINSTANCE hInstance;
HWND hWnd;
WNDCLASSEX wc;

int ClientWidth;
int ClientHeight;
	bool isInitialized = false;

	Win32App();
	bool Initialize();
};