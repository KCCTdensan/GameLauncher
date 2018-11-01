#pragma once

#include "MemDC.hpp"

#ifndef INCLUDE_BUTTON_HPP
#define INCLUDE_BUTTON_HPP


class button :public mem_dc
{
	unsigned short x;
	unsigned short y;

public:
	button(unsigned short Width, unsigned short Height);
	~button();
	void SetPosition(unsigned short x, unsigned short y);
	bool PointInButtonRect(unsigned short x, unsigned short y)const;
	void Paint(HDC hDC)const;
	RECT GetAbsoluteRect()const;
	RECT GetRelativeRect()const;
};


#endif