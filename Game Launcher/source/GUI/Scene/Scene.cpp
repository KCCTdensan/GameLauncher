#include "Scene.hpp"


Color Scene::ColorBkgnd(RGB(0x1f, 0x1f, 0x1f));
Color Scene::ColorAccent[MAX_CATEGORY] = {
	RGB(0xdf, 0x3f, 0x3f),
	RGB(0xbf, 0xbf, 0x3f),
	RGB(0xaf, 0x2f, 0x9f),
	RGB(0x2f, 0xaf, 0xaf),
	RGB(0x2f, 0x5f, 0xdf),
	RGB(0x2f, 0xdf, 0x5f),
	RGB(0x7f, 0x7f, 0x7f)
};

Scene::Scene(SceneChangerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight) :MemDC(BmpWidth, BmpHeight)
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
	BitBlt(hdc, 0, 0, Width, Height, hMemDC, 0, 0, SRCCOPY);
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