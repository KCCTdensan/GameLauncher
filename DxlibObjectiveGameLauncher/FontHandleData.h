#pragma once
#include <string>

struct FontHandle {
	std::string fontName;
	std::string handleName;
	int size;
	int thick;
	int type;

	FontHandle(std::string handleName, std::string fontName)
		: handleName(handleName), fontName(fontName), size(24), thick(-1), type(2) {}
	FontHandle(std::string handleName, std::string fontName, int size, int thick = -1, int type = 2)
		: handleName(handleName), fontName(fontName), size(size), thick(thick), type(type) {}
};