#pragma once
#include "SceneBase.h"
#include "ButtonObject.h"
#include "DebugScene.h"
#include "SceneManager.h"

class HomeScene :
    public SceneBase
{
public:
    HomeScene();

    void Collide();
    void Update();
    void Draw();

private :
    ButtonObject debugButton;
};

