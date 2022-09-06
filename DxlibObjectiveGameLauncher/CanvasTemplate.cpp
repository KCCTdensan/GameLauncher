#include "CanvasTemplate.h"

CanvasTemplate::CanvasTemplate()
{
}

void CanvasTemplate::CanvasCollide()
{
	canvases.Collide();
}

void CanvasTemplate::CanvasUpdate()
{
	canvases.Update();
}

void CanvasTemplate::CanvasDraw()
{
	canvases.Draw();
}

void CanvasTemplate::ItemCollide()
{
	layer.Collide();
}

void CanvasTemplate::ItemUpdate()
{
	layer.Update();
}

void CanvasTemplate::ItemDraw()
{
	layer.Draw();
}
