#include "MyApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
{
    MyApp appInstance(hInstance);

    appInstance.Init();
    appInstance.Run();
    return 0;
}