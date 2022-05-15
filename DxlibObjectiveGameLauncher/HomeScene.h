#pragma once
#include "SceneBase.h"
#include "ButtonObject.h"
#include "SceneManager.h"
#include "DebugScene.h"

class HomeScene :
    public SceneBase
{
public:
    HomeScene();

    void Update();
    void Draw();

private :
    ButtonObject debugButton;
};
