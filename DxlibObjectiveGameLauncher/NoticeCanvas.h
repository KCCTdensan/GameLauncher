#pragma once
#include "CanvasTemplate.h"
#include "OriginalObjects.h"
#include "ColorPreset.h"
#include "NoticeObject.h"

class NoticeCanvas :
    public CanvasTemplate
{
public:
    NoticeCanvas();

    void UpdateAction() override;

private:

    CanvasObject* canvas;
    std::vector<NoticeObject*> notices;

};

