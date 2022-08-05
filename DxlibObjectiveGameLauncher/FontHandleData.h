#pragma once
#include <string>

struct FontHandle {
	std::string fontName;
	std::string handleName;
	int size;
	int thick;
	int type;

	FontHandle(std::string _handleName, std::string _fontName)
		: handleName(_handleName), fontName(_fontName), size(24), thick(-1), type(2) {}
	FontHandle(std::string _handleName, std::string _fontName, int _size, int _thick = -1, int _type = 2)
		: handleName(_handleName), fontName(_fontName), size(_size), thick(_thick), type(_type) {}
};