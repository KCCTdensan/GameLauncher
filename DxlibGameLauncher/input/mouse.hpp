#pragma once

#include "../position.hpp"
#include "../size.hpp"
#include <Windows.h>


namespace input
{
	enum class MouseInputID
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
		const Size backgroundSize;
		const Size clientSize;
		Position cursorPosition;
		int buttonInput;

	public:
		Mouse(Size backgroundSize, Size clientSize);
		void update();
		Position getCursorPosition()const;
		int getMouseButtonInput()const;
	};
}