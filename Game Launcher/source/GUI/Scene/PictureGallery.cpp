#include "PictureGallery.hpp"


PictureGallery::PictureGallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(Interface, BmpWidth, BmpHeight)
{

}

PictureGallery::~PictureGallery()
{

}

int PictureGallery::Initialize(HWND hWnd)
{
	return 0;
}

int PictureGallery::Finalize(HWND hWnd)
{
	return 0;
}

int PictureGallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int PictureGallery::Update(HWND hWnd)
{
	return 0;
}