#pragma once

#include "../position.hpp"
#include "../size.hpp"


namespace input
{
	enum MouseInputID
	{
		MouseInputLeft,
		MouseInputRight,
		MouseInputMiddle,
		MouseInput4,
		MouseInput5,
		MouseInput6,
		MouseInput7,
		MouseInput8
	};

	class Mouse
	{
		Size clientSize;
		Position cursorPosition;
		MouseInputID buttonInput;

	public:
		Mouse(HWND mainWindowHandle);
		void update();
		Position getCursorPosition();
	};
}