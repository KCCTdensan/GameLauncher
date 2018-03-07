#pragma once

#include "scene.hpp"

#ifndef INCLUDE_STARTUP_HPP
#define INCLUDE_STARTUP_HPP


class StartUp :public Scene
{
public:
	StartUp(HWND hWnd, unsigned short BmpWidth, unsigned short BmpHeight);
	~StartUp();
	int Initialize(HWND hWnd);
	int Finalize(HWND hWnd);
	int Paint(HWND hWnd);
};


#endif