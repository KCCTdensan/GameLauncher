#include "OthersGallery.hpp"


OthersGallery::OthersGallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(Interface, BmpWidth, BmpHeight, RGB(0xaf, 0xaf, 0xaf))
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
	return 0;
}

int OthersGallery::Update(HWND hWnd)
{
	return 0;
}
