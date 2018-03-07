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
		GetClientRect(hWnd, &WindowRect);//クライアントエリアのサイズを取得
		SceneManager = new MasterScene(hWnd, Scene_StartUp, WindowRect.right, WindowRect.bottom);
	}
		ShowWindow(hWnd, SW_SHOW);
		return 0;

	case WM_DESTROY:
		SceneManager->Finalize(hWnd);
		delete SceneManager;
		SceneManager = nullptr;
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		return SceneManager->Paint(hWnd);

	case WM_MOUSEMOVE:
		return SceneManager->MouseMove(hWnd, wp, lp);

	case WM_LBUTTONDOWN:
		return SceneManager->LButtonDown(hWnd, wp, lp);

	case WM_LBUTTONUP:
		return SceneManager->LButtonUp(hWnd, wp, lp);

	case WM_RBUTTONDOWN:
		return SceneManager->RButtonDown(hWnd, wp, lp);

	case WM_RBUTTONUP:
		return SceneManager->RButtonUp(hWnd, wp, lp);

	case WM_GUI_UPDATE:
		return SceneManager->Update(hWnd);

	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}