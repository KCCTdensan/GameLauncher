#pragma once

#include <Windows.h>

#ifndef INCLUDE_COLOR_HPP
#define INCLUDE_COLOR_HPP


class Color
{
	COLORREF Code;
	HBRUSH hBrush;
	HPEN hPen;

public:
	Color(COLORREF ColorCode);
	~Color();
	void Rectangle(HDC hDC, RECT &Rect);
	void Rectangle(HDC hDC, int Left, int Top, int Right, int Bottom);
};


#endif