#pragma once
#include "SceneBase.h"
#include "SceneManager.h"
#include "HomeScene.h"
class BlankRedirectScene :
    public SceneBase
{
public:
    BlankRedirectScene() {}

    void Update();
    void Draw() {}
};

