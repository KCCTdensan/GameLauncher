#include "scene.hpp"


Scene::Scene(unsigned short BmpWidth, unsigned short BmpHeight) :MemDC(BmpWidth, BmpHeight)
{

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
	HDC hdc = GetDC(hWnd);
	BitBlt(hdc, 0, 0, GetWidth(), GetHeight(), GethMemDC(), 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);
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