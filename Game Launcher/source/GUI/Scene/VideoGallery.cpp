#include "VideoGallery.hpp"


VideoGallery::VideoGallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(Interface, BmpWidth, BmpHeight, RGB(0x2f, 0xdf, 0x5f))
{

}

VideoGallery::~VideoGallery()
{

}

int VideoGallery::Initialize(HWND hWnd)
{
	return 0;
}

int VideoGallery::Finalize(HWND hWnd)
{
	return 0;
}

int VideoGallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int VideoGallery::Update(HWND hWnd)
{
	return 0;
}
