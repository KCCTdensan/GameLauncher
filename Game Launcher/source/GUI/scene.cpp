#include "scene.hpp"


Scene::Scene(unsigned short BmpWidth, unsigned short BmpHeight) :MemDC(BmpWidth, BmpHeight)
{

}

int Scene::Update(HWND hWnd)
{
	return 0;
}

int Scene::Paint(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	BitBlt(hdc, 0, 0, GetWidth(), GetHeight(), GethMemDC(), 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);
	return 0;
}

int Scene::ChangeScene(HWND hWnd, int NextScene)
{
	return 0;
}