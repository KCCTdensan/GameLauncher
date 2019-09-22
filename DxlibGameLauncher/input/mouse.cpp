#include "mouse.hpp"
#include "../AppData.h"
#include <DxLib.h>


namespace input
{
	Mouse::Mouse(HWND mainWindowHandle)
	{
		RECT clientRect;
		GetClientRect(mainWindowHandle, &clientRect);
		clientSize.width = clientRect.right - clientRect.left;
		clientSize.height = clientRect.bottom - clientRect.top;
	}

	void Mouse::update()
	{
		Position mousePosition;
		GetMousePoint(&mousePosition.x, &mousePosition.y);
		cursorPosition.x = mousePosition.x * App::BackgroundSize.width / clientSize.width;
		cursorPosition.y = mousePosition.y * App::BackgroundSize.height / clientSize.height;
		buttonInput = static_cast<MouseInputID>(GetMouseInput());
	}

	Position Mouse::getCursorPosition()
	{
		return cursorPosition;
	}
}