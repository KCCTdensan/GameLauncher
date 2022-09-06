#pragma once
#include "ObjectLayer.h"

class CanvasTemplate
{
public:
	CanvasTemplate();

    void CanvasCollide();
    void CanvasUpdate();
    void CanvasDraw();

    void ItemCollide();
    void ItemUpdate();
    void ItemDraw();

    virtual void UpdateAction() = 0;

private:
    ObjectLayer canvases;
    ObjectLayer layer;
};
