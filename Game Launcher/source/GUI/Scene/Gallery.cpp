#include "Gallery.hpp"


Gallery::Gallery(SceneChangerInterface*SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight) :Scene(SceneChanger, BmpWidth, BmpHeight)
{
	hBrushBkgnd = CreateSolidBrush(BkgndColor);
	hPenBkgnd = CreatePen(PS_SOLID, 0, BkgndColor);
}

Gallery::~Gallery()
{
	HDC hdc = GethMemDC();
	SelectObject(hdc, GetStockObject(NULL_BRUSH));//hMemDC���܂��j������Ă��Ȃ��̂ŁA�ʂ̃u���V��I�����Ă���
	SelectObject(hdc, GetStockObject(NULL_PEN));//hMemDC���܂��j������Ă��Ȃ��̂ŁA�ʂ̃y����I�����Ă���
	DeleteObject(hBrushBkgnd);
	DeleteObject(hPenBkgnd);
	hBrushBkgnd = NULL;
	hPenBkgnd = NULL;
}