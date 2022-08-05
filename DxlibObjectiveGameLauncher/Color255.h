#pragma once
#include "DxLib.h"

struct Color255 {
	int r;
	int g;
	int b;
	int a;
	Color255(int _grayScale)
		:r(_grayScale), g(_grayScale), b(_grayScale), a(255) {}
	Color255(int _grayScale, int _a)
		:r(_grayScale), g(_grayScale), b(_grayScale), a(_a) {}
	Color255(int _r, int _g, int _b)
		:r(_r), g(_g), b(_b), a(255) {}
	Color255(int _r, int _g, int _b, int _a)
		:r(_r), g(_g), b(_b), a(_a) {}
	int Get() { return GetColor(r, g, b); }
};