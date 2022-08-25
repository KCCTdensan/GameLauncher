#pragma once
#include "ObjectLayer.h"

class PopupWindow
{
public:
	PopupWindow()
	: canvases(), layer() {}

	void Setup(ObjectLayer* _canvases, ObjectLayer* _layer);

	void CollideLayer();
	void CollideCanvas();
	void UpdateLayer();
	void UpdateCanvas();
	void DrawLayer();
	void DrawCanvas();

	ObjectLayer* GetCanvases() { return canvases; }
	ObjectLayer* GetLayer() { return layer; }

private:

	ObjectLayer* canvases;
	ObjectLayer* layer;
};

