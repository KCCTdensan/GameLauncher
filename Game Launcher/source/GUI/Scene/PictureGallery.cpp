#include "PictureGallery.hpp"


picture_gallery::picture_gallery(HWND hWnd, scene_manager_interface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:gallery(Interface, BmpWidth, BmpHeight)
{
	Items = ItemManager::GetItems(CAT_PICTURE);
}

picture_gallery::~picture_gallery()
{

}

int picture_gallery::Initialize(HWND hWnd)
{
	DrawBkgnd();
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int picture_gallery::Finalize(HWND hWnd)
{
	return 0;
}

int picture_gallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int picture_gallery::Update(HWND hWnd)
{
	return 0;
}