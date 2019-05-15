#include "main_menu.hpp"


void MainMenu::drawBackground()
{
	SelectObject(hMemDC, hBrushBkgnd);
	SelectObject(hMemDC, hPenBkgnd);
	Rectangle(hMemDC, 0, 0, width, height);
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
}

MainMenu::MainMenu(HWND hWnd, SceneChangerInterface* SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight)
	:Scene(hWnd, SceneChanger, BmpWidth, BmpHeight)
{
	hBrushBkgnd = CreateSolidBrush(BkgndColor);
	hPenBkgnd = CreatePen(PS_SOLID, 0, BkgndColor);
}

MainMenu::~MainMenu()
{
	SelectObject(hMemDC, GetStockObject(NULL_BRUSH));//hMemDCがまだ破棄されていないので、別のブラシを選択しておく
	SelectObject(hMemDC, GetStockObject(NULL_PEN));//hMemDCがまだ破棄されていないので、別のペンを選択しておく
	DeleteObject(hBrushBkgnd);
	DeleteObject(hPenBkgnd);
	hBrushBkgnd = NULL;
	hPenBkgnd = NULL;
}

int MainMenu::initialize()
{
	drawBackground();
	return 0;
}

int MainMenu::finalize()
{
	return 0;
}

int MainMenu::buttonLUp(unsigned short x, unsigned short y)
{
	DestroyWindow(hWnd);//virtual
	return 0;
}

int MainMenu::update()
{
	return 0;
}