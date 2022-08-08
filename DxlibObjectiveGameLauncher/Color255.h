#pragma once
#include "DxLib.h"
#include <string>

struct Color255 {
public:
	int r;
	int g;
	int b;
	int a;
	Color255(int _grayScale) // グレースケール(0~255)
		:r(_grayScale), g(_grayScale), b(_grayScale), a(255) {}
	Color255(int _grayScale, int _a) // グレースケール(0~255), アルファ(0~255)
		:r(_grayScale), g(_grayScale), b(_grayScale), a(_a) {}
	Color255(int _r, int _g, int _b) // (r, g, b) each (0~255)
		:r(_r), g(_g), b(_b), a(255) {}
	Color255(int _r, int _g, int _b, int _a) // (r, g, b, alpha) each (0~255)
		:r(_r), g(_g), b(_b), a(_a) {}
	Color255(std::string code) // ("#00ff00"{or "00ff00"})
		: a(255)
	{
		std::string formalCode = code;
		formalCode = SplitSharp(formalCode);
		int value = std::stoi(formalCode, nullptr, 16);
		r = value / (256 * 256);
		g = (value / 256) % 256;
		b = value % 256;
	}
	Color255(std::string code, int _a) // ("#00ff00"{or "00ff00"}, alpha) alpha:(0~255)
		: a(_a)
	{
		std::string formalCode = code;
		formalCode = SplitSharp(formalCode);
		int value = std::stoi(formalCode, nullptr, 16);
		r = value / (256 * 256);
		g = (value / 256) % 256;
		b = value % 256;
	}
	// Dxlibで使える色値を返す
	int Get() { return GetColor(r, g, b); }
private:
	std::string SplitSharp(std::string code) {
		std::string result = code;
		if (code.find("#") != std::string::npos) {
			result = code.substr(1);
		}
		return result;
	}
};