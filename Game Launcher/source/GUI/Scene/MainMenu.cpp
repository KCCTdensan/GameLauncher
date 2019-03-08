#include "MainMenu.hpp"


MainMenu::MainMenu(HWND hWnd, SceneChangerInterface* SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight) :Scene(SceneChanger, BmpWidth, BmpHeight)
{
	hBrushBkgnd = CreateSolidBrush(BkgndColor);
	hPenBkgnd = CreatePen(PS_SOLID, 0, BkgndColor);
}

MainMenu::~MainMenu()
{
	SelectObject(hMemDC, GetStockObject(NULL_BRUSH));//hMemDC���܂��j������Ă��Ȃ��̂ŁA�ʂ̃u���V��I�����Ă���
	SelectObject(hMemDC, GetStockObject(NULL_PEN));//hMemDC���܂��j������Ă��Ȃ��̂ŁA�ʂ̃y����I�����Ă���
	DeleteObject(hBrushBkgnd);
	DeleteObject(hPenBkgnd);
	hBrushBkgnd = NULL;
	hPenBkgnd = NULL;
}

int MainMenu::Initialize(HWND hWnd)
{
	//�w�i��h��Ԃ�
	SelectObject(hMemDC, hBrushBkgnd);
	SelectObject(hMemDC, hPenBkgnd);
	Rectangle(hMemDC, 0, 0, Width, Height);
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);

	return 0;
}

int MainMenu::Finalize(HWND hWnd)
{
	return 0;
}

int MainMenu::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	DestroyWindow(hWnd);
	return 0;
}

int MainMenu::Update(HWND hWnd)
{
	return 0;
}