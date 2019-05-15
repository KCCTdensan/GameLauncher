#include "Scene.hpp"


Scene::Scene(HWND hWnd, SceneChangerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:MemDC(BmpWidth, BmpHeight), Task(hWnd)
{
	Scene::SceneChanger = SceneChanger;
}

int Scene::paint()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	BitBlt(hdc, 0, 0, Width, Height, hMemDC, 0, 0, SRCCOPY);
	EndPaint(hWnd, &ps);
	return 0;
}