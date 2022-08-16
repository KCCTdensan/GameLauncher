#include "MouseInput.h"

PosVec Input::MouseInput::mouse = PosVec();
PosVec Input::MouseInput::mouseWin = PosVec();
MouseClickType Input::MouseInput::mouseClickType = MouseClickType();
int Input::MouseInput::mouseInputs = 0;
float Input::MouseInput::wheelRot = 0;

void Input::MouseInput::Update()
{
	int x, y;
	GetMousePoint(&x, &y);
	mouse.x = (float)x;
	mouse.y = (float)y;

	mouseWin.x = static_cast<float>(mouse.x /* * WINDOW_SIZE_RATE_TIME */);
	mouseWin.y = static_cast<float>(mouse.y /* * WINDOW_SIZE_RATE_TIME */);
	mouseInputs = GetMouseInput();

	UpdateClick(&mouseClickType.left, MOUSE_INPUT_LEFT);
	UpdateClick(&mouseClickType.right, MOUSE_INPUT_RIGHT);
	UpdateClick(&mouseClickType.middle, MOUSE_INPUT_MIDDLE);
	UpdateClick(&mouseClickType.mouse4, MOUSE_INPUT_4);
	UpdateClick(&mouseClickType.mouse5, MOUSE_INPUT_5);

	wheelRot = GetMouseWheelRotVolF();
}

int Input::MouseInput::GetClick(int _button)
{
	switch (_button) // MOUSE_INPUT_XX
	{
	case MOUSE_INPUT_LEFT:
		return mouseClickType.left;
	case MOUSE_INPUT_RIGHT:
		return mouseClickType.right;
	case MOUSE_INPUT_MIDDLE:
		return mouseClickType.middle;
	case MOUSE_INPUT_4:
		return mouseClickType.mouse4;
	case MOUSE_INPUT_5:
		return mouseClickType.mouse5;
	default:
		return -1;
	}
	return -1;
}

void Input::MouseInput::UpdateClick(int* _value, int _andValue)
{
	if ((mouseInputs & _andValue) != 0)
	{
		if (*_value >= PressFrame::FIRST) {
			*_value = PressFrame::MUCH;
		}
		else {
			*_value = PressFrame::FIRST;
		}
	}
	else {
		if (*_value == PressFrame::MUCH) *_value = PressFrame::RELEASE;
		*_value = PressFrame::ZERO;
	}
}