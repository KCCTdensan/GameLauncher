#include "Window.hpp"


window::window(unsigned short BmpWidth, unsigned short BmpHeight)
	:mem_dc(BmpWidth, BmpHeight)
{
	PositionX = 0;
	PositionY = 0;
	Width = 0;
	Height = 0;
	OffsetX = 0;
	OffsetY = 0;
}

window::~window()
{

}

void window::SetWindowSize(unsigned short Width, unsigned short Height)
{
	this->Width = Width;
	this->Height = Height;
}

void window::SetPosition(unsigned short x, unsigned short y)
{
	PositionX = x;
	PositionY = y;
}

void window::SetOffset(unsigned short x, unsigned short y)
{
	OffsetX = x;
	OffsetY = y;
}

void window::Paint(HDC hDC)
{
	BitBlt(hDC, PositionX, PositionY, Width, Height, hMemDC, OffsetX, OffsetY, SRCCOPY);
}
