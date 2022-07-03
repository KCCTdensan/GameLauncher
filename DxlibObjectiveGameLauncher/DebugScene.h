#pragma once
#include "SceneBase.h"
#include "ButtonObject.h"
#include "RectangleObject.h"
#include "HomeScene.h"
#include "ApplicationPreference.h"

class DebugScene :
    public SceneBase
{
public:
    DebugScene();

    void Collide();
    void Update();
    void Draw();

private:
    RectangleObject bg;
    ButtonObject debugButton;
    ButtonObject debugButton2;
    RectangleObject debugRect;
};

