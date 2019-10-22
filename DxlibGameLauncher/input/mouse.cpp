#include "mouse.hpp"
#include "../AppData.h"
#include <DxLib.h>


namespace input
{
	Mouse::Mouse(Size backgroundSize, Size clientSize)
		: backgroundSize(backgroundSize), clientSize(clientSize), cursorPosition{0, 0}, buttonInput(0)
	{

	}

	void Mouse::update()
	{
		Position mousePosition;
		GetMousePoint(&mousePosition.x, &mousePosition.y);
		cursorPosition.x = mousePosition.x * App::BackgroundSize.width / clientSize.width;
		cursorPosition.y = mousePosition.y * App::BackgroundSize.height / clientSize.height;
		buttonInput = GetMouseInput();
	}

	Position Mouse::getCursorPosition()
	{
		return cursorPosition;
	}

	int Mouse::getMouseButtonInput()
	{
		return buttonInput;
	}
}