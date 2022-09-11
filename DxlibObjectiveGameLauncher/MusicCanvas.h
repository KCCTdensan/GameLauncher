#pragma once
#include "CanvasTemplate.h"
#include "OriginalObjects.h"

class MusicCanvas :
    public CanvasTemplate
{
public:
    MusicCanvas();

    void UpdateAction() override;

private:

    CanvasObject canvas;
    ButtonObject button;
};

