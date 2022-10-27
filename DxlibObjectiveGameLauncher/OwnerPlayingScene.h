#pragma once
#include "SceneBase.h"
#include "OriginalObjects.h"
#include "SceneManager.h"

class OwnerPlayingScene :
    public SceneBase
{
public:
    OwnerPlayingScene();
    OwnerPlayingScene(SharingScenes* _sharingScenes);

    void Collide();
    void Update();
    void Draw();

private:

    void SetMiddleCenterText(ButtonObject* button);

    int noticeGenerateNum;
    int noticeGenerated;

    CanvasObject* canvas;
    RectangleObject* bg;

    TextObject* title;

    ButtonObject* button1;
    ButtonObject* button2;
    ButtonObject* button3;
    ButtonObject* button4;
    ButtonObject* button5;
    ButtonObject* button6;
    ButtonObject* button7;

    RectangleObject* rect1;

    ProgressObject* progress1;

    InputObject* input1;
};

