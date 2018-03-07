#include "mainmenu.hpp"


MainMenu::MainMenu(HWND hWnd, unsigned short BmpWidth, unsigned short BmpHeight) :Scene(BmpWidth, BmpHeight)
{
	hBrushBkgnd = CreateSolidBrush(RGB(0x3f, 0x3f, 0x3f));
}

MainMenu::~MainMenu()
{
	SelectObject(GethMemDC(), GetStockObject(NULL_BRUSH));//hMemDC‚ª‚Ü‚¾”jŠü‚³‚ê‚Ä‚¢‚È‚¢‚Ì‚ÅA•Ê‚Ìƒuƒ‰ƒV‚ğ‘I‘ğ‚µ‚Ä‚¨‚­
	DeleteObject(hBrushBkgnd);
	hBrushBkgnd = NULL;
}

int MainMenu::Initialize(HWND hWnd)
{
	HDC hdc = GethMemDC();

	//”wŒi‚ğ“h‚è‚Â‚Ô‚·
	SelectObject(hdc, hBrushBkgnd);
	Rectangle(hdc, 0, 0, GetWidth(), GetHeight());

	return 0;
}

int MainMenu::Finalize(HWND hWnd)
{
	return 0;
}

int MainMenu::ChangeScene(HWND hWnd, int NextScene)
{
	return 0;
}