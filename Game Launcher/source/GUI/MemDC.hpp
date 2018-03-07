#pragma once

#ifndef INCLUDE_MEMDC_HPP
#define INCLUDE_MEMDC_HPP

#include <Windows.h>


class MemDC
{
	unsigned short w;
	unsigned short h;
	HDC hMemDC;
	HBITMAP hMemBmp;

	void PrepareMemDC();
	void UnprepareMemDC();

public:
	MemDC(unsigned short Width, unsigned short Height);
	~MemDC();
	void Paint(HDC hDC);
	HDC GethMemDC();
	unsigned short GetWidth();
	unsigned short GetHeight();
};


#endif