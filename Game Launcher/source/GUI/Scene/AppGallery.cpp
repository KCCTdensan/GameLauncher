#include "AppGallery.hpp"


app_gallery::app_gallery(HWND hWnd, scene_manager_interface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:gallery(SceneChanger, CAT_APP, BmpWidth, BmpHeight)
{

}

app_gallery::~app_gallery()
{

}

int app_gallery::Initialize(HWND hWnd)
{
	DrawBkgnd();
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int app_gallery::Finalize(HWND hWnd)
{
	return 0;
}

int app_gallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int app_gallery::Update(HWND hWnd)
{
	return 0;
}
