#pragma once

#ifndef INCLUDE_MEMDC_HPP
#define INCLUDE_MEMDC_HPP

#include <Windows.h>


class mem_dc
{
	HBITMAP hMemBmp;

	void PrepareMemDC();
	void UnprepareMemDC();

public:
	const HDC hMemDC;
	const unsigned short Width;
	const unsigned short Height;

	mem_dc(unsigned short Width, unsigned short Height);
	~mem_dc();
	void Paint(HDC hDC)const;
	void Paint(HDC hDC, int x, int y)const;
};


#endif