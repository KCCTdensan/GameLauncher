#pragma once
#include "SceneBase.h"
#include "OriginalObjects.h"
#include "DebugScene.h"
#include "SceneManager.h"

class HomeScene :
    public SceneBase
{
public:
    HomeScene();
    HomeScene(SharingScenes* _sharingScenes);

    void Collide();
    void Update();
    void Draw();

private :
    ButtonObject debugButton;
};

