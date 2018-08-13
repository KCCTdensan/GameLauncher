#include "ModelGallery.hpp"


ModelGallery::ModelGallery(HWND hWnd, SceneChangerInterface *Interface, unsigned short BmpWidth, unsigned short BmpHeight)
	:Gallery(Interface, BmpWidth, BmpHeight)
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
	DestroyWindow(hWnd);
	return 0;
}

int ModelGallery::Update(HWND hWnd)
{
	return 0;
}
