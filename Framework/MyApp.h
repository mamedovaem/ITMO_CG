#pragma once
#include <WindowsX.h>
#include "D3DApp.h"

class MyApp : public D3DApp
{
public:
	MyApp(HINSTANCE hInstance) :  D3DApp(hInstance) {}
	~MyApp() {}

	virtual bool Init();
	virtual void OnResize();
	virtual void UpdateScene(float dt);
	virtual void DrawScene();
};
