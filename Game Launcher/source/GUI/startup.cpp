#include "startup.hpp"


StartUp::StartUp(HWND hWnd, unsigned short BmpWidth, unsigned short BmpHeight) :Scene(BmpWidth, BmpHeight)
{
	hBrushBkgnd = CreateSolidBrush(RGB(0x1f, 0x1f, 0x1f));
}

StartUp::~StartUp()
{	
	SelectObject(GethMemDC(), GetStockObject(NULL_BRUSH));//hMemDC���܂��j������Ă��Ȃ��̂ŁA�ʂ̃u���V��I�����Ă���
	DeleteObject(hBrushBkgnd);
	hBrushBkgnd = NULL;
}

int StartUp::Initialize(HWND hWnd)
{
	HDC hdc = GethMemDC();

	//�w�i��h��Ԃ�
	SelectObject(hdc, hBrushBkgnd);
	Rectangle(hdc, 0, 0, GetWidth(), GetHeight());

	return 0;
}

int StartUp::Finalize(HWND hWnd)
{
	return 0;
}