#include "VideoGallery.hpp"


video_gallery::video_gallery(HWND hWnd, scene_manager_interface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:gallery(Interface, BmpWidth, BmpHeight)
{
	Items = ItemManager::GetItems(CAT_VIDEO);
}

video_gallery::~video_gallery()
{

}

int video_gallery::Initialize(HWND hWnd)
{
	DrawBkgnd();
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int video_gallery::Finalize(HWND hWnd)
{
	return 0;
}

int video_gallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int video_gallery::Update(HWND hWnd)
{
	return 0;
}
