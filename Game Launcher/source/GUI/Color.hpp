#pragma once

#include <Windows.h>

#ifndef INCLUDE_COLOR_HPP
#define INCLUDE_COLOR_HPP


class Color
{
	COLORREF Code;
	COLORREF SubCode;
	HBRUSH hBrush;
	HBRUSH hBrushSub;
	HPEN hPen;
	HPEN hPenSub;

public:
	Color(COLORREF ColorCode);
	~Color();
	void Rectangle(HDC hDC, RECT &Rect);
	void Rectangle(HDC hDC, int Left, int Top, int Right, int Bottom);
	void RectangleGradation(HDC hDC, RECT &Rect);
	void RectangleGradation(HDC hDC, int Left, int Top, int Right, int Bottom);
};


#endif