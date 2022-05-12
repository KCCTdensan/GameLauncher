#pragma once
#include "PositionVector.h"
#include "MouseClickType.h"
#include "PressFrameEnum.h"
#include "DxLib.h"

namespace Input {
	class MouseInput
	{
	public:
		static void Update();
		static PosVec GetMouse() { return mouse; }
		static PosVec GetMouseWindow() { return mouseWin; }

	private:

		static PosVec mouse;
		static PosVec mouseWin;

		static MouseClickType mouseClickType;

		// and 演算により必要なクリックを取り出す
		static int mouseInputs;//MOUSE_INPUT_LEFT MOUSE_INPUT_RIGHT MOUSE_INPUT_MIDDLE MOUSE_INPUT_4 MOUSE_INPUT_5 MOUSE_INPUT_6 MOUSE_INPUT_7 MOUSE_INPUT_8
	};
}

	PosVec Input::MouseInput::mouse = PosVec();
	PosVec Input::MouseInput::mouseWin = PosVec();
	MouseClickType Input::MouseInput::mouseClickType = MouseClickType();
	int Input::MouseInput::mouseInputs = 0;
