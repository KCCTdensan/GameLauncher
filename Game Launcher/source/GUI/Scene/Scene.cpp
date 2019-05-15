#include "Scene.hpp"


Scene::Scene(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:MemDC(BmpWidth, BmpHeight), Task(hWnd)
{
	Scene::sceneChanger = sceneChanger;
}

int Scene::paint()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	BitBlt(hdc, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);
	EndPaint(hWnd, &ps);
	return 0;
}