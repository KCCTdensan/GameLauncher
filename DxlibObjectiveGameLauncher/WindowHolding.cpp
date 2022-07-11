#include "WindowHolding.h"

PosVec WindowHolding::holdingWindowPos = PosVec();
POINT WindowHolding::po = POINT();

void WindowHolding::Update()
{
	if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) >= PressFrame::FIRST && Input::MouseInput::GetMouse().y <= ApplicationPreference::GetBackgroundSize().y / 12.f) {
		GetCursorPos(&po);
		if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) == PressFrame::FIRST) {
			int x, y;
			GetWindowPosition(&x, &y);
			holdingWindowPos.x = (float)po.x - (float)x;
			holdingWindowPos.y = (float)po.y - (float)y;
		}
		SetWindowPosition(po.x - (int)holdingWindowPos.x, po.y - (int)holdingWindowPos.y);
	}
}
