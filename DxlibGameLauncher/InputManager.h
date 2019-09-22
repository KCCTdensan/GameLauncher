#pragma once

#define KEYBOARD_PRESS_ZERO 0
#define KEYBOARD_PRESS_FIRST 1
#define KEYBOARD_PRESS_MUCH 2


namespace Input
{
	class KeyBoard
	{
	public:
		KeyBoard();
		~KeyBoard();

		static void Update();
		static int KEY[256];

	};

	class Mouse
	{
	public:
		Mouse();
		~Mouse();

		static void Update();

		static int MOUSE_X;
		static int MOUSE_Y;

		static int MOUSE_WIN_X;
		static int MOUSE_WIN_Y;

		static int MOUSE_CLICK;//MOUSE_INPUT_LEFT MOUSE_INPUT_RIGHT MOUSE_INPUT_MIDDLE MOUSE_INPUT_4 MOUSE_INPUT_5 MOUSE_INPUT_6 MOUSE_INPUT_7 MOUSE_INPUT_8
		
	};
}