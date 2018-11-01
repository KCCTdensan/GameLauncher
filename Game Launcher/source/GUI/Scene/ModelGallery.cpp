#include "ModelGallery.hpp"


model_gallery::model_gallery(HWND hWnd, scene_manager_interface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:gallery(Interface,CAT_3DMODEL, BmpWidth, BmpHeight)
{
	
}

model_gallery::~model_gallery()
{
}

int model_gallery::Initialize(HWND hWnd)
{
	DrawBkgnd();
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int model_gallery::Finalize(HWND hWnd)
{
	return 0;
}

int model_gallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int model_gallery::Update(HWND hWnd)
{
	return 0;
}
