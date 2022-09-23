#include "MusicCanvas.h"

MusicCanvas::MusicCanvas()
{
	canvas = new CanvasObject(PosVec(900, 400), PosVec(500, 300));
	canvas->SetInnerColor(Color255(255, 0, 0));
	canvas->SetArea(PosVec(1000, 500));

	button = new ButtonObject();
	canvas->RegisterChildren(button);

	layer.AddObject(button);
	canvases.AddObject(canvas);
}

void MusicCanvas::UpdateAction()
{
}
