#include "others_gallery.hpp"


OthersGallery::OthersGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight)
	:Gallery(hWnd, sceneChanger, bmpWidth, bmpHeight)
{

}

int OthersGallery::initialize()
{
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int OthersGallery::finalize()
{
	return 0;
}

int OthersGallery::buttonLUp(unsigned short x, unsigned short y, unsigned int param)
{
	return 0;
}

int OthersGallery::update()
{
	return 0;
}
