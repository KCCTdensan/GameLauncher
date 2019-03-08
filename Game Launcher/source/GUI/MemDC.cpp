#include "MemDC.hpp"


void MemDC::PrepareMemDC()
{
	HDC hdc = GetDC(NULL);
	hMemBmp = CreateCompatibleBitmap(hdc, Width, Height);
	SelectObject(hMemDC, hMemBmp);
	ReleaseDC(NULL, hdc);
}

void MemDC::UnprepareMemDC()
{
	DeleteDC(hMemDC);
	DeleteObject(hMemBmp);
}

MemDC::MemDC(unsigned short Width, unsigned short Height) :hMemDC(CreateCompatibleDC(NULL)), Width(Width), Height(Height)
{
	PrepareMemDC();
}

MemDC::~MemDC()
{
	UnprepareMemDC();
}

void MemDC::Paint(HDC hDC)const
{
	BitBlt(hDC, 0, 0, Width, Height, hMemDC, 0, 0, SRCCOPY);
}

void MemDC::Paint(HDC hDC, int x, int y)const
{
	BitBlt(hDC, x, y, Width, Height, hMemDC, 0, 0, SRCCOPY);
}
