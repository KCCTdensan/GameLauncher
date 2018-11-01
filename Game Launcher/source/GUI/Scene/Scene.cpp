#include "Scene.hpp"


color scene::ColorBkgnd(RGB(0x0f, 0x0f, 0x0f));

scene::scene(scene_manager_interface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight) :mem_dc(BmpWidth, BmpHeight)
{
	scene::SceneChanger = SceneChanger;
}

int scene::Initialize(HWND hWnd)
{
	return 0;
}

int scene::Finalize(HWND hWnd)
{
	return 0;
}

int scene::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int scene::RButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int scene::RButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int scene::Update(HWND hWnd)
{
	return 0;
}

int scene::Paint(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	BitBlt(hdc, 0, 0, Width, Height, hMemDC, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);
	return 0;
}

int scene::MouseMove(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int scene::LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}