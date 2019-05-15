#pragma once

#ifndef INCLUDE_MEM_DC_HPP
#define INCLUDE_MEM_DC_HPP

#include <Windows.h>


class MemDC
{
	HBITMAP hMemBmp;

	void prepareMemDC();
	void unprepareMemDC();

public:
	HDC hMemDC;
	const unsigned short width;
	const unsigned short height;

	MemDC(unsigned short width, unsigned short height);
	~MemDC();
	void paint(HDC hDC)const;
	void paint(HDC hDC, int x, int y)const;
};


#endif