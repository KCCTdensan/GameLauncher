#pragma once
#include "SceneBase.h"
#include "OriginalObjects.h"
#include "SceneManager.h"
// 任意読込
#include "lib/picojson.h"
#include <fstream>
#include <cassert>
#include <iostream> // std::cout
#include <sstream>
#include <numbers>
#include <vector>

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

    picojson::object obj;

    /* 紹介用オブジェクト */
    ImageObject* thumbnail;
    TextObject* category;
    TextObject* title;
    TextObject* author;
    TextObject* guidText;
    TextObject* description;
    CanvasObject* descriptionCanvas;
    CanvasObject* thumbnailCanvas;
    std::vector<LineObject*> descriptionLines;

    ButtonObject* launch;

    RectangleObject* thumbnailBackGround;

    /* 紹介用オブジェクト */

    std::string guid;

    // buffer
    PosVec thumbnailPos;
    PosVec thumbnailSize;

    const float maxImageLongLengthOnBig = 800.f;
    const float zoomFrame = .5f;
};

