#include "MusicCanvas.h"

MusicCanvas::MusicCanvas()
{
	canvases.AddObject(&canvas);
	canvas = CanvasObject(PosVec(900, 400), PosVec(500, 300));
	canvas.SetInnerColor(Color255(255, 0, 0));
	canvas.SetArea(PosVec(1000, 500));
	canvas.RegisterChildren(&button);
	layer.AddObject(&button);
}

void MusicCanvas::UpdateAction()
{
}
