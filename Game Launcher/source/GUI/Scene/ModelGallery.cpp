#include "ModelGallery.hpp"


ModelGallery::ModelGallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(Interface, BmpWidth, BmpHeight, RGB(0x2f, 0x5f, 0xdf))
{

}

ModelGallery::~ModelGallery()
{
}

int ModelGallery::Initialize(HWND hWnd)
{
	return 0;
}

int ModelGallery::Finalize(HWND hWnd)
{
	return 0;
}

int ModelGallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int ModelGallery::Update(HWND hWnd)
{
	return 0;
}
