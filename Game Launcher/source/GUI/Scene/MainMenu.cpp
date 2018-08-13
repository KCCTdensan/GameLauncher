#include "MainMenu.hpp"
#include "wmsg.h"


MainMenu::MainMenu(HWND hWnd, SceneManagerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:Scene(SceneChanger, BmpWidth, BmpHeight)
{
	int Split = ((MAX_CATEGORY / 2) + 1) * 2;
	int Block = BmpWidth / Split;
	int GalleryButtonWidth = Block * 5 / 6;
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		GalleryButtonDCs[i] = new MemDC(GalleryButtonWidth, GalleryButtonWidth);
		GalleryButtonRects[i].left = (Split == MAX_CATEGORY) ? Block * i + Block / 10 : Block * i + Block / 2 + Block / 10;
		GalleryButtonRects[i].top = (BmpHeight - GalleryButtonWidth) / 2;
		GalleryButtonRects[i].right = GalleryButtonRects[i].left + GalleryButtonWidth;
		GalleryButtonRects[i].bottom = GalleryButtonRects[i].top + GalleryButtonWidth;
		ColorAccent[i].RectangleGradation(GalleryButtonDCs[i]->hMemDC, 0, 0, GalleryButtonWidth, GalleryButtonWidth);
	}
}

MainMenu::~MainMenu()
{
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		delete GalleryButtonDCs[i];
	}
}

int MainMenu::Initialize(HWND hWnd)
{
	ColorBkgnd.Rectangle(hMemDC, 0, 0, Width, Height);
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		BitBlt(hMemDC, GalleryButtonRects[i].left, GalleryButtonRects[i].top, GalleryButtonRects[i].right - GalleryButtonRects[i].left, GalleryButtonRects[i].bottom - GalleryButtonRects[i].top,
			   GalleryButtonDCs[i]->hMemDC, 0, 0, SRCCOPY);
	}
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);

	return 0;
}

int MainMenu::Finalize(HWND hWnd)
{
	return 0;
}

int MainMenu::LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return 0;
}

int MainMenu::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lp);
	MousePoint.y = HIWORD(lp);
	for(int i = 0; i < MAX_CATEGORY; ++i)
	{
		if(PtInRect(&GalleryButtonRects[i], MousePoint))
		{
			PostMessage(hWnd, WM_GUI_CHANGESCENE, i + 1, 0);
			break;
		}
	}
	return 0;
}

int MainMenu::Update(HWND hWnd)
{
	return 0;
}