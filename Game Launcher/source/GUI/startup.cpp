#include "startup.hpp"


StartUp::StartUp(HWND hWnd, unsigned short BmpWidth, unsigned short BmpHeight) :Scene(BmpWidth, BmpHeight)
{
	hBrushBkgnd = CreateSolidBrush(RGB(0x1f, 0x1f, 0x1f));
}

StartUp::~StartUp()
{	
	SelectObject(GethMemDC(), GetStockObject(NULL_BRUSH));//hMemDC‚ª‚Ü‚¾”jŠü‚³‚ê‚Ä‚¢‚È‚¢‚Ì‚ÅA•Ê‚Ìƒuƒ‰ƒV‚ğ‘I‘ğ‚µ‚Ä‚¨‚­
	DeleteObject(hBrushBkgnd);
	hBrushBkgnd = NULL;
}

int StartUp::Initialize(HWND hWnd)
{
	HDC hdc = GethMemDC();

	//”wŒi‚ğ“h‚è‚Â‚Ô‚·
	SelectObject(hdc, hBrushBkgnd);
	Rectangle(hdc, 0, 0, GetWidth(), GetHeight());

	return 0;
}

int StartUp::Finalize(HWND hWnd)
{
	return 0;
}