#include "Color.hpp"


color::color(COLORREF ColorCode)
{
	Code = ColorCode;
	unsigned char rs = (unsigned char)Code / 2;
	unsigned char gs = (unsigned char)(Code >> 8) / 2;
	unsigned char bs = (unsigned char)(Code >> 16) / 2;
	SubCode = RGB(rs, gs, bs);
	hBrush = CreateSolidBrush(Code);
	hBrushSub = CreateSolidBrush(SubCode);
	hPen = CreatePen(PS_SOLID, 0, Code);
	hPenSub = CreatePen(PS_SOLID, 0, SubCode);
}

color::~color()
{
	DeleteObject(hBrush);
	DeleteObject(hBrushSub);
	DeleteObject(hPen);
	DeleteObject(hPenSub);
}

void color::Rectangle(HDC hDC, RECT &Rect)const
{
	Rectangle(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom);
}

void color::Rectangle(HDC hDC, int Left, int Top, int Right, int Bottom)const
{
	SelectObject(hDC, hBrush);
	SelectObject(hDC, hPen);
	::Rectangle(hDC, Left, Top, Right, Bottom);
}

void color::RectangleGradation(HDC hDC, RECT &Rect)const
{
	RectangleGradation(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom);
}

void color::RectangleGradation(HDC hDC, int Left, int Top, int Right, int Bottom)const
{
	unsigned char r = (unsigned char)Code;
	unsigned char g = (unsigned char)(Code >> 8);
	unsigned char b = (unsigned char)(Code >> 16);
	unsigned char rs = (unsigned char)SubCode;
	unsigned char gs = (unsigned char)(SubCode >> 8);
	unsigned char bs = (unsigned char)(SubCode >> 16);
	int Height = Bottom - Top;
	for(int i = 0; i < Height; ++i)
	{
		unsigned char rc = (unsigned char)((r * (Height - i) + rs * i) / Height);
		unsigned char gc = (unsigned char)((g * (Height - i) + gs * i) / Height);
		unsigned char bc = (unsigned char)((b * (Height - i) + bs * i) / Height);
		COLORREF CurrentColor = RGB(rc, gc, bc);
		HPEN hPenCurrent = CreatePen(PS_SOLID, 0, CurrentColor);
		SelectObject(hDC, hPenCurrent);
		MoveToEx(hDC, Left, Top + i, NULL);
		LineTo(hDC, Right, Top + i);
		SelectObject(hDC, GetStockObject(NULL_PEN));
		DeleteObject(hPenCurrent);
	}
}
