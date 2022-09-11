#pragma once
#include "SceneBase.h"
#include "HomeScene.h"
#include "ApplicationPreference.h"
#include "OriginalObjects.h"
#include "FontChest.h"
#include "ObjectLayer.h"
#include "lib/picojson.h"
#include <vector>
#include <fstream>
#include <cassert>
#include <iostream> // std::cout
#include <sstream>
#include <string>

class DebugScene :
    public SceneBase
{
public:
    DebugScene();
    DebugScene(SharingScenes* _sharingScenes);
    ~DebugScene();

    void Collide();
    void Update();
    void Draw();

private:
    CanvasObject canvas;
    CanvasObject canvas2;
    RectangleObject bg;
    ButtonObject debugButton;
    ButtonObject debugButton2;
    RectangleObject debugRect;
    TextObject textSample1;
    InputObject input;
    InputObject input2;
    RectangleObject pallet;
    ProgressObject progress;

    CanvasObject can;

    ButtonObject cofb;

    std::vector<ButtonObject> works;

};

