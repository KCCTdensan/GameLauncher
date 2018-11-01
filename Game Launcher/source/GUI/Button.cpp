#include "Button.hpp"


button::button(unsigned short Width, unsigned short Height)
	:mem_dc(Width, Height)
{
	x = 0;
	y = 0;
}

button::~button()
{

}

void button::SetPosition(unsigned short x, unsigned short y)
{
	this->x = x;
	this->y = y;
}

bool button::PointInButtonRect(unsigned short x, unsigned short y)const
{
	RECT Rect;
	Rect.left = x;
	Rect.top = y;
	Rect.right = x + Width;
	Rect.bottom = y + Height;
	return PtInRect(&Rect, POINT{ x,y }) != 0;
}

void button::Paint(HDC hDC)const
{
	BitBlt(hDC, x, y, Width, Height, hMemDC, 0, 0, SRCCOPY);
}
