#include "window_procedure.hpp"
#include "item_manager.hpp"
#include "GUI/scene_manager.hpp"
#include "wmsg.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static SceneManager *sceneManager = nullptr;
	static ItemManager itemManager;

	switch (msg)
	{
	case WM_CREATE:
		SendMessage(hWnd, WM_ITEM_SCAN, 0, 0);
		sceneManager = new SceneManager(hWnd, SceneName_MainMenu, ((LPCREATESTRUCT)lp)->cx, ((LPCREATESTRUCT)lp)->cy);
		sceneManager->initialize();
		ShowWindow(hWnd, SW_SHOW);
		return 0;

	case WM_DESTROY:
		sceneManager->finalize();
		delete sceneManager;
		sceneManager = nullptr;
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		return sceneManager->paint();

	case WM_ERASEBKGND:
		return true;

	case WM_MOUSEMOVE:
		return sceneManager->mouseMove(LOWORD(lp), HIWORD(lp), (unsigned int)wp);

	case WM_LBUTTONDOWN:
		return sceneManager->buttonLDown(LOWORD(lp), HIWORD(lp));

	case WM_LBUTTONUP:
		return sceneManager->buttonLUp(LOWORD(lp), HIWORD(lp));

	case WM_RBUTTONDOWN:
		return sceneManager->buttonRDown(LOWORD(lp), HIWORD(lp));

	case WM_RBUTTONUP:
		return sceneManager->buttonRUp(LOWORD(lp), HIWORD(lp));

	case WM_ITEM_SCAN:
		return itemManager.scanItems(L"Works/");

	case WM_ITEM_CLEAR:
		itemManager.clearItems();
		return 0;

	case WM_GUI_UPDATE:
		return sceneManager->update();

	case WM_GUI_CHANGESCENE:
		return sceneManager->changeScene((SceneName)wp);

	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}