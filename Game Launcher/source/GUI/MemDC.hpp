#pragma once

#ifndef INCLUDE_MEMDC_HPP
#define INCLUDE_MEMDC_HPP

#include <Windows.h>


class MemDC
{
	HBITMAP hMemBmp;

	void PrepareMemDC();
	void UnprepareMemDC();

public:
	const HDC hMemDC;
	const unsigned short Width;
	const unsigned short Height;

	MemDC(unsigned short Width, unsigned short Height);
	~MemDC();
	void Paint(HDC hDC)const;
	void Paint(HDC hDC, int x, int y)const;
};


#endif