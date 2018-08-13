#include "VideoGallery.hpp"


VideoGallery::VideoGallery(HWND hWnd, SceneManagerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(Interface, BmpWidth, BmpHeight)
{

}

VideoGallery::~VideoGallery()
{

}

int VideoGallery::Initialize(HWND hWnd)
{
	DrawBkgnd();
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int VideoGallery::Finalize(HWND hWnd)
{
	return 0;
}

int VideoGallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int VideoGallery::Update(HWND hWnd)
{
	return 0;
}
