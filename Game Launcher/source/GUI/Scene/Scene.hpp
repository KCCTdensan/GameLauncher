#pragma once

#include "../MemDC.hpp"
#include "../Task.hpp"
#include "../SceneChangerInterface.hpp"
#include "../Color.hpp"
#include "contents.hpp"

#ifndef INCLUDE_SCENE_HPP
#define INCLUDE_SCENE_HPP


class Scene :public MemDC, public Task
{
protected:
	static Color ColorBkgnd;
	static Color ColorAccent[MAX_CATEGORY];
	SceneManagerInterface *SceneChanger;

public:
	Scene(SceneManagerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	virtual int Initialize(HWND hWnd);
	virtual int Finalize(HWND hWnd);
	virtual int Paint(HWND hWnd);
	virtual int MouseMove(HWND hWnd, WPARAM wp, LPARAM lp);
	virtual int LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp);
	virtual int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	virtual int RButtonDown(HWND hWnd, WPARAM wp, LPARAM lp);
	virtual int RButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);
	virtual int Update(HWND hWnd);
};


#endif