#include "MainMenu.hpp"
#include "Gallery.hpp"
#include "wmsg.h"


main_menu::main_menu(HWND hWnd, scene_manager_interface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:scene(SceneChanger, BmpWidth, BmpHeight)
{
	int Split = ((MAX_CATEGORY / 2) + 1) * 2;
	int Block = BmpWidth / Split;
	int GalleryButtonWidth = Block * 5 / 6;
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		GalleryButtons[i] = new button(GalleryButtonWidth, GalleryButtonWidth);
		GalleryButtons[i]->SetPosition((Split == MAX_CATEGORY) ? Block * i + Block / 10 : Block * i + Block / 2 + Block / 10, (BmpHeight - GalleryButtonWidth) / 2);
		gallery::ColorAccent[i].RectangleGradation(GalleryButtons[i]->hMemDC, 0, 0, GalleryButtonWidth, GalleryButtonWidth);
	}
}

main_menu::~main_menu()
{
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		delete GalleryButtons[i];
	}
}

int main_menu::Initialize(HWND hWnd)
{
	ColorBkgnd.Rectangle(hMemDC, 0, 0, Width, Height);
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		GalleryButtons[i]->Paint(hMemDC);
	}
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);

	return 0;
}

int main_menu::Finalize(HWND hWnd)
{
	return 0;
}

int main_menu::LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int main_menu::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	unsigned short x = LOWORD(lp);
	unsigned short y = HIWORD(lp);
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		if (GalleryButtons[i]->PointInButtonRect(x, y))
		{
			PostMessage(hWnd, WM_GUI_CHANGESCENE, i + SceneName_AppGallery, 0);
			break;
		}
	}
	return 0;
}

int main_menu::Update(HWND hWnd)
{
	return 0;
}