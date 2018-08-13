#include "MusicGallery.hpp"


MusicGallery::MusicGallery(HWND hWnd, SceneManagerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(Interface, BmpWidth, BmpHeight)
{

}

MusicGallery::~MusicGallery()
{

}

int MusicGallery::Initialize(HWND hWnd)
{
	DrawBkgnd();
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int MusicGallery::Finalize(HWND hWnd)
{
	return 0;
}

int MusicGallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int MusicGallery::Update(HWND hWnd)
{
	return 0;
}
