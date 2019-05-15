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
	Gallery::buttonLUp(hWnd, wp, lp);
	return 0;
}

int AppGallery::Update(HWND hWnd)
{
	return 0;
}
