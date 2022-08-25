#include "PopupWindow.h"

void PopupWindow::Setup(ObjectLayer* _canvases, ObjectLayer* _layer)
{
	canvases = _canvases;
	layer = _layer;
}

void PopupWindow::CollideLayer()
{
	if (layer == nullptr) return;
	layer->Collide();
}

void PopupWindow::CollideCanvas()
{
	if (canvases == nullptr) return;
	canvases->Collide();
}

void PopupWindow::UpdateLayer()
{
	if (layer == nullptr) return;
	layer->Update();
}

void PopupWindow::UpdateCanvas()
{
	if (canvases == nullptr) return;
	canvases->Update();
}

void PopupWindow::DrawLayer()
{
	if (layer == nullptr) return;
	layer->Draw();
}

void PopupWindow::DrawCanvas()
{
	if (canvases == nullptr) return;
	canvases->Draw();
}
