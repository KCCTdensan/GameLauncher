#pragma once
#include "SceneBase.h"
class DebugScene :
    public SceneBase
{
public:
    DebugScene() {}

    virtual void Update();
    virtual void Draw();
};

