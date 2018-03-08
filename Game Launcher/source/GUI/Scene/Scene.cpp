#include "Scene.hpp"


Scene::Scene(SceneChangerInterface*SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight) :MemDC(BmpWidth, BmpHeight)
{
	Scene::SceneChanger = SceneChanger;
}

int Scene::Initialize(HWND hWnd)
{
	return 0;
}

int Scene::Finalize(HWND hWnd)
{
	return 0;
}

int Scene::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int Scene::RButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int Scene::RButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int Scene::Update(HWND hWnd)
{
	return 0;
}

int Scene::Paint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	BitBlt(hdc, 0, 0, GetWidth(), GetHeight(), GethMemDC(), 0, 0, SRCCOPY);
	EndPaint(hWnd, &ps);
	return 0;
}

int Scene::MouseMove(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int Scene::LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}