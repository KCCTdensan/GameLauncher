#pragma once

#include "Scene.hpp"

#ifndef INCLUDE_STARTUP_HPP
#define INCLUDE_STARTUP_HPP


class StartUp :public Scene
{
	const static COLORREF BkgndColor = RGB(0x1f, 0x1f, 0x1f);
	HANDLE hThread;
	unsigned int ThreadID;
	HBRUSH hBrushBkgnd;//�w�i�h��Ԃ��p
	HPEN hPenBkgnd;//�w�i�h��Ԃ��p

	static unsigned int __stdcall Thread(void*Arg);

public:
	StartUp(HWND hWnd, SceneChangerInterface*SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	~StartUp();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int Update(HWND hWnd);
};


#endif