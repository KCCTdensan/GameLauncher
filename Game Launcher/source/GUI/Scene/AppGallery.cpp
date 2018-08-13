#include "AppGallery.hpp"


AppGallery::AppGallery(HWND hWnd, SceneChangerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(SceneChanger, BmpWidth, BmpHeight)
{

}

AppGallery::~AppGallery()
{

}

int AppGallery::Initialize(HWND hWnd)
{
	ColorBkgnd.Rectangle(hMemDC, 0, 0, Width, Height);
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int AppGallery::Finalize(HWND hWnd)
{
	return 0;
}

int AppGallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int AppGallery::Update(HWND hWnd)
{
	return 0;
}
