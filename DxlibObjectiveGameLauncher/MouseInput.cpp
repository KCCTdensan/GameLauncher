#include "MouseInput.h"

PosVec Input::MouseInput::mouse = PosVec();
PosVec Input::MouseInput::mouseWin = PosVec();
MouseClickType Input::MouseInput::mouseClickType = MouseClickType();
int Input::MouseInput::mouseInputs = 0;

void Input::MouseInput::Update()
{
	int x, y;
	GetMousePoint(&x, &y);
	mouse.x, mouse.y = (float)x, (float)y;

	mouseWin.x = static_cast<float>(mouse.x /* * WINDOW_SIZE_RATE_TIME */);
	mouseWin.y = static_cast<float>(mouse.y /* * WINDOW_SIZE_RATE_TIME */);
	mouseInputs = GetMouseInput();
	if ((mouseInputs & MOUSE_INPUT_LEFT) != 0)
	{
		if (mouseClickType.left >= PressFrame::FIRST) {
			mouseClickType.left = PressFrame::MUCH;
		}
		else {
			mouseClickType.left = PressFrame::FIRST;
		}
	}
	else {
		mouseClickType.left = PressFrame::ZERO;
	}
}
