#pragma once
#include "SceneBase.h"
#include "ButtonObject.h"
#include "SceneManager.h"
#include "HomeScene.h"

class DebugScene :
    public SceneBase
{
public:
    DebugScene();

    void Update();
    void Draw();

private:
    ButtonObject debugButton;
    ButtonObject debugButton2;
};

