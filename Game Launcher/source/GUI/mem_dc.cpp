#include "mem_dc.hpp"


void MemDC::prepareMemDC()
{
	HDC hdc = GetDC(NULL);
	hMemBmp = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(hMemDC, hMemBmp);
	ReleaseDC(NULL, hdc);
}

void MemDC::unprepareMemDC()
{
	DeleteDC(hMemDC);
	DeleteObject(hMemBmp);
}

MemDC::MemDC(unsigned short width, unsigned short height)
	:hMemDC(CreateCompatibleDC(NULL)), width(width), height(height)
{
	prepareMemDC();
}

MemDC::~MemDC()
{
	unprepareMemDC();
}

void MemDC::paint(HDC hDC)const
{
	BitBlt(hDC, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);
}

void MemDC::paint(HDC hDC, int x, int y)const
{
	BitBlt(hDC, x, y, width, height, hMemDC, 0, 0, SRCCOPY);
}
