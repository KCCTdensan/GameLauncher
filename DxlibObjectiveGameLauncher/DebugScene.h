#pragma once
#include "SceneBase.h"
#include "HomeScene.h"
#include "ApplicationPreference.h"
#include "OriginalObjects.h"
#include "FontChest.h"

class DebugScene :
    public SceneBase
{
public:
    DebugScene();
    ~DebugScene();

    void Collide();
    void Update();
    void Draw();

private:
    RectangleObject bg;
    ButtonObject debugButton;
    ButtonObject debugButton2;
    RectangleObject debugRect;
    TextObject textSample1;
    InputObject input;
    InputObject input2;
};

