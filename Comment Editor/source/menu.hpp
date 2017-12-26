#pragma once

#include <Windows.h>

#ifndef INCLUDE_MENU_HPP
#define INCLUDE_MENU_HPP


namespace MENU
{
	void CreateWndMenu(HWND hWnd);
	void onWM_COMMAND(HWND hWnd, WPARAM wp);
}


#endif