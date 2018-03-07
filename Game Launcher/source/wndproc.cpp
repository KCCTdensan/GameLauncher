#include "wndproc.hpp"
#include "GUI/masterscene.hpp"
#include <wmsg.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static MasterScene*SceneManager = nullptr;

	switch (msg)
	{
	case WM_CREATE:
	{
		RECT WindowRect;
		GetClientRect(hWnd, &WindowRect);
		SceneManager = new MasterScene(hWnd, Scene_StartUp, WindowRect.right, WindowRect.bottom);
	}
		ShowWindow(hWnd, SW_SHOW);
		return 0;

	case WM_DESTROY:
		delete SceneManager;
		SceneManager = nullptr;
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		SceneManager->Paint(hWnd);
		return 0;

	case WM_LBUTTONUP:
		DestroyWindow(hWnd);
		return 0;

	case WM_GUI_UPDATE:
		SceneManager->Update(hWnd);
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}