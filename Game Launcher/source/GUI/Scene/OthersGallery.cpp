#include "OthersGallery.hpp"


OthersGallery::OthersGallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(Interface, BmpWidth, BmpHeight)
{

}

OthersGallery::~OthersGallery()
{

}

int OthersGallery::Initialize(HWND hWnd)
{
	return 0;
}

int OthersGallery::Finalize(HWND hWnd)
{
	return 0;
}

int OthersGallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int OthersGallery::Update(HWND hWnd)
{
	return 0;
}
