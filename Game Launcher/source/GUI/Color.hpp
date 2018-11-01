#pragma once

#include <Windows.h>

#ifndef INCLUDE_COLOR_HPP
#define INCLUDE_COLOR_HPP


class color
{
	COLORREF Code;
	COLORREF SubCode;
	HBRUSH hBrush;
	HBRUSH hBrushSub;
	HPEN hPen;
	HPEN hPenSub;

public:
	color(COLORREF ColorCode);
	~color();
	void Rectangle(HDC hDC, RECT &Rect)const;
	void Rectangle(HDC hDC, int Left, int Top, int Right, int Bottom)const;
	void RectangleGradation(HDC hDC, RECT &Rect)const;
	void RectangleGradation(HDC hDC, int Left, int Top, int Right, int Bottom)const;
};


#endif