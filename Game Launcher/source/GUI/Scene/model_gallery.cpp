#include "model_gallery.hpp"


ModelGallery::ModelGallery(HWND hWnd, SceneChangerInterface *sceneChanger, unsigned short bmpWidth, unsigned short bmpHeight)
	:Gallery(hWnd, sceneChanger, bmpWidth, bmpHeight)
{

}

int ModelGallery::initialize()
{
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
	return 0;
}

int ModelGallery::finalize()
{
	return 0;
}

int ModelGallery::buttonLUp(unsigned short x, unsigned short y, unsigned int param)
{
	return 0;
}

int ModelGallery::update()
{
	return 0;
}
