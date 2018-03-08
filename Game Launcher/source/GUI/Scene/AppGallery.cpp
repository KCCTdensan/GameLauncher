#include "AppGallery.hpp"


AppGallery::AppGallery(HWND hWnd, SceneChangerInterface*SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight) :Scene(SceneChanger, BmpWidth, BmpHeight)
{

}

int AppGallery::Initialize(HWND hWnd)
{
	return 0;
}

int AppGallery::Finalize(HWND hWnd)
{
	return 0;
}

int AppGallery::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int AppGallery::Update(HWND hWnd)
{
	return 0;
}
