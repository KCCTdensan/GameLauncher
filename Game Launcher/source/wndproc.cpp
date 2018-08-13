#include "WndProc.hpp"
#include "GUI/SceneManager.hpp"
#include <wmsg.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static SceneManager *Scene = nullptr;

	switch (msg)
	{
	case WM_CREATE:
		Scene = new SceneManager(hWnd, SceneName_MainMenu, ((LPCREATESTRUCT)lp)->cx, ((LPCREATESTRUCT)lp)->cy);
		Scene->Initialize(hWnd);
		ShowWindow(hWnd, SW_SHOW);
		return 0;

	case WM_DESTROY:
		Scene->Finalize(hWnd);
		delete Scene;
		Scene = nullptr;
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		return Scene->Paint(hWnd);

	case WM_ERASEBKGND:
		return true;

	case WM_MOUSEMOVE:
		return Scene->MouseMove(hWnd, wp, lp);

	case WM_LBUTTONDOWN:
		return Scene->LButtonDown(hWnd, wp, lp);

	case WM_LBUTTONUP:
		return Scene->LButtonUp(hWnd, wp, lp);

	case WM_RBUTTONDOWN:
		return Scene->RButtonDown(hWnd, wp, lp);

	case WM_RBUTTONUP:
		return Scene->RButtonUp(hWnd, wp, lp);

	case WM_GUI_UPDATE:
		return Scene->Update(hWnd);

	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}