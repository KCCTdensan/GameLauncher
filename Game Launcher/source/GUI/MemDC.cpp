#include "MemDC.hpp"


void MemDC::PrepareMemDC()
{
	HDC hdc = GetDC(NULL);
	hMemBmp = CreateCompatibleBitmap(hdc, w, h);
	hMemDC = CreateCompatibleDC(NULL);
	SelectObject(hMemDC, hMemBmp);
	ReleaseDC(NULL, hdc);
}

void MemDC::UnprepareMemDC()
{
	DeleteDC(hMemDC);
	DeleteObject(hMemBmp);
}

MemDC::MemDC(unsigned short Width, unsigned short Height)
{
	w = Width;
	h = Height;
	PrepareMemDC();
}

MemDC::~MemDC()
{
	UnprepareMemDC();
}

void MemDC::Paint(HDC hDC)
{
	BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
}

HDC MemDC::GethMemDC()
{
	return hMemDC;
}

unsigned short MemDC::GetWidth()
{
	return w;
}

unsigned short MemDC::GetHeight()
{
	return h;
}