#pragma once
#include "CanvasTemplate.h"

class PopupWindow
{
public:
    PopupWindow();

    void Setup(CanvasTemplate* _cTemplate);

    void CanvasCollide();
    void CanvasUpdate();
    void CanvasDraw();

    void ItemCollide();
    void ItemUpdate();
    void ItemDraw();

    void UpdateAction();

private:
    CanvasTemplate* cTemplate;
};

