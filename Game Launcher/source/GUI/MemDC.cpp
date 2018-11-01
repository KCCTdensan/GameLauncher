#include "MemDC.hpp"


void mem_dc::PrepareMemDC()
{
	HDC hdc = GetDC(NULL);
	hMemBmp = CreateCompatibleBitmap(hdc, Width, Height);
	SelectObject(hMemDC, hMemBmp);
	ReleaseDC(NULL, hdc);
}

void mem_dc::UnprepareMemDC()
{
	DeleteDC(hMemDC);
	DeleteObject(hMemBmp);
}

mem_dc::mem_dc(unsigned short Width, unsigned short Height) :hMemDC(CreateCompatibleDC(NULL)), Width(Width), Height(Height)
{
	PrepareMemDC();
}

mem_dc::~mem_dc()
{
	UnprepareMemDC();
}

void mem_dc::Paint(HDC hDC)const
{
	BitBlt(hDC, 0, 0, Width, Height, hMemDC, 0, 0, SRCCOPY);
}

void mem_dc::Paint(HDC hDC, int x, int y)const
{
	BitBlt(hDC, x, y, Width, Height, hMemDC, 0, 0, SRCCOPY);
}
