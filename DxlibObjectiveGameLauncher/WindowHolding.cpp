#include "WindowHolding.h"

PosVec WindowHolding::holdingWindowPos = PosVec();
POINT WindowHolding::po = POINT();
bool WindowHolding::windowMaximized = false;
bool WindowHolding::holding = false;

void WindowHolding::Update()
{
	if (IsZoomed(GetMainWindowHandle()) == 0) windowMaximized = false;
	else windowMaximized = true;
	if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) >= PressFrame::FIRST && Input::MouseInput::GetMouse().y <= ApplicationPreference::GetBackgroundSize().y / 15.f) {
		GetCursorPos(&po); // モニター上のポインタの位置
		if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) == PressFrame::FIRST) {
			int x, y;
			GetWindowPosition(&x, &y); // クライアント位置を取得
			holdingWindowPos.x = (float)po.x - (float)x;
			holdingWindowPos.y = (float)po.y - (float)y;
			holding = true;
		}
		if (windowMaximized) {
			int x, y;
			GetWindowPosition(&x, &y); // クライアント位置を取得
			if (x != po.x - (int)holdingWindowPos.x || y != po.y - (int)holdingWindowPos.y) {
				windowMaximized = false;
				WindowHwnd::WindowNormalize(GetMainWindowHandle());
				int x, y;
				GetWindowPosition(&x, &y); // クライアント位置を取得
				holdingWindowPos.x = (float)po.x - (float)x;
				holdingWindowPos.y = (float)po.y - (float)y + (int)(GetSystemMetrics(SM_CYCAPTION) * 1.2f);
			}
		} else if (holding) SetWindowPosition(po.x - (int)holdingWindowPos.x, po.y - (int)holdingWindowPos.y);
	}
	if (holding && Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) <= PressFrame::ZERO) {
		GetCursorPos(&po);
		if (po.y <= 5) {
			WindowHwnd::WindowMaximize(GetMainWindowHandle());
		}
		holding = false;
	}
}
