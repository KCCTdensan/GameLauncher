#include "Color.hpp"


Color::Color(COLORREF ColorCode)
{
	Code = ColorCode;
	hBrush = CreateSolidBrush(Code);
	hPen = CreatePen(PS_SOLID, 0, Code);
}

Color::~Color()
{
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void Color::Rectangle(HDC hDC, RECT &Rect)
{
	Rectangle(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom);
}

void Color::Rectangle(HDC hDC, int Left, int Top, int Right, int Bottom)
{
	SelectObject(hDC, hBrush);
	SelectObject(hDC, hPen);
	::Rectangle(hDC, Left, Top, Right, Bottom);
}
