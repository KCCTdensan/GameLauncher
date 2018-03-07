#pragma once

#include <Windows.h>
#include "MemDC.hpp"

#ifndef INCLUDE_SCENE_HPP
#define INCLUDE_SCENE_HPP


class Scene :public MemDC
{
public:
	Scene(unsigned short BmpWidth, unsigned short BmpHeight);
	virtual int Initialize(HWND hWnd) = 0;
	virtual int Finalize(HWND hWnd) = 0;
	virtual int Update(HWND hWnd);
	virtual int Paint(HWND hWnd);
	virtual int ChangeScene(HWND hWnd, int NextScene);
};


#endif