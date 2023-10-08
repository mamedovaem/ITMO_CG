#pragma once
#include <WindowsX.h>
#include <d3d11.h>
#include <dxgi.h>
#include <dxgiformat.h>
#include <time.h>
#include <string>
#include <DirectXColors.h>
#include <DirectXMath.h>

#ifdef _DEBUG
	#ifndef HR
	#define HR(x)\
		{\
			HRESULT hr = (x);\
			if (FAILED(hr))\
				{\
					/*DXTrace(__FILE__, (DWORD)__LINE__, hr, L"#x", true);*/\
				}\
		}
	#endif 
#else 
	#ifndef HR 
	#define HR(x) (x) 
	#endif 
#endif
