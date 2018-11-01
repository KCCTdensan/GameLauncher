#pragma once

#include "MemDC.hpp"

#ifndef INCLUDE_WINDOW_HPP
#define INCLUDE_WINDOW_HPP


class window :public mem_dc
{
	unsigned short PositionX;
	unsigned short PositionY;
	unsigned short Width;
	unsigned short Height;
	unsigned short OffsetX;
	unsigned short OffsetY;

public:
	window(unsigned short BmpWidth, unsigned short BmpHeight);
	~window();
	void SetWindowSize(unsigned short Width, unsigned short Height);
	void SetPosition(unsigned short x, unsigned short y);
	void SetOffset(unsigned short x, unsigned short y);
	void Paint(HDC hDC);
};


#endif