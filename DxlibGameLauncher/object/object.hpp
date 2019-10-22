#pragma once

#include "../position.hpp"
#include "../size.hpp"
#include <string>
#include <DxLib.h>


namespace object
{
	class Object
	{
	protected:
		bool isValid;
		std::wstring name;
		int graphHandle;
		Position position;
		Size size;

	public:
		Object(std::wstring name, int graphHandle, Position position, Size size);
		void draw();
		bool isCursorOnObject(Position cursorPosition);
	};
}