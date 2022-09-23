#pragma once
#include "SceneBase.h"
#include "OriginalObjects.h"
#include "SceneManager.h"
// îCà”ì«çû
#include "lib/picojson.h"
#include <fstream>
#include <cassert>
#include <iostream> // std::cout
#include <sstream>
#include <numbers>

#include "WorkScene.h"

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
    CanvasObject* canvas;
    RectangleObject* bg;
    std::vector<ButtonObject*> works;
};

