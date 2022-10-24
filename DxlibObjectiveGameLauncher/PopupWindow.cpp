#include "PopupWindow.h"

PopupWindow::PopupWindow()
	: cTemplate(nullptr)
{

}

void PopupWindow::Setup(CanvasTemplate* _cTemplate)
{
	cTemplate = _cTemplate;
}

void PopupWindow::CanvasCollide()
{
	if (cTemplate == nullptr) return;
	cTemplate->CanvasCollide();
}

void PopupWindow::CanvasUpdate()
{
	if (cTemplate == nullptr) return;
	cTemplate->CanvasUpdate();
}

void PopupWindow::CanvasDraw()
{
	if (cTemplate == nullptr) return;
	cTemplate->CanvasDraw();
}

void PopupWindow::ItemCollide()
{
	if (cTemplate == nullptr) return;
	cTemplate->ItemCollide();
}

void PopupWindow::ItemUpdate()
{
	if (cTemplate == nullptr) return;
	cTemplate->ItemUpdate();
}

void PopupWindow::ItemDraw()
{
	if (cTemplate == nullptr) return;
	cTemplate->ItemDraw();
}

void PopupWindow::UpdateAction()
{
	if (cTemplate == nullptr) return;
	cTemplate->UpdateAction();
}
