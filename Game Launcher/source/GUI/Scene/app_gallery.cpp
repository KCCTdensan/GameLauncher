#include "app_gallery.hpp"


AppGallery::AppGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight)
	:Gallery(hWnd, sceneChanger, bmpWidth, bmpHeight)
{

}

int AppGallery::initialize()
{
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int AppGallery::finalize()
{
	return 0;
}

int AppGallery::buttonLUp(unsigned short x, unsigned short y, unsigned int param)
{
	return 0;
}

int AppGallery::update()
{
	return 0;
}