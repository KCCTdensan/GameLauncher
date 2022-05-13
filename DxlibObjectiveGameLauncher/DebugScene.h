#pragma once
#include "SceneBase.h"
#include "ButtonObject.h"

class DebugScene :
    public SceneBase
{
public:
    DebugScene();

    virtual void Update();
    virtual void Draw();

private:
    ButtonObject debugButton;
};

