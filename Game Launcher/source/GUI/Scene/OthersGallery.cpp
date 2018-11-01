#include "OthersGallery.hpp"


others_gallery::others_gallery(HWND hWnd, scene_manager_interface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:gallery(Interface,CAT_OTHERS, BmpWidth, BmpHeight)
{
	
}

others_gallery::~others_gallery()
{

}

int others_gallery::Initialize(HWND hWnd)
{
	DrawBkgnd();
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int others_gallery::Finalize(HWND hWnd)
{
	return 0;
}

int others_gallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int others_gallery::Update(HWND hWnd)
{
	return 0;
}
