#include "Scene.hpp"


Scene::Scene(SceneChangerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:MemDC(BmpWidth, BmpHeight)
{
	Scene::SceneChanger = SceneChanger;
}

int Scene::Paint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	BitBlt(hdc, 0, 0, Width, Height, hMemDC, 0, 0, SRCCOPY);
	EndPaint(hWnd, &ps);
	return 0;
}