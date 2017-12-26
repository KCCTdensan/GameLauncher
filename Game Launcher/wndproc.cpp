#include "wndproc.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONUP:
		DestroyWindow(hWnd);
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}