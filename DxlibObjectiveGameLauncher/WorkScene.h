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

class WorkScene :
    public SceneBase
{
public:
    WorkScene();
    WorkScene(SharingScenes* _sharingScenes, std::string workGuid);

    void Collide();
    void Update();
    void Draw();

private:
    CanvasObject canvas;
    RectangleObject bg;

    std::string guid;
};

