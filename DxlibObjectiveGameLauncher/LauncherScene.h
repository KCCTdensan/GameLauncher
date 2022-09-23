#pragma once
#include "SceneBase.h"
#include "OriginalObjects.h"
#include "SceneManager.h"
// �C�ӓǍ�
#include "lib/picojson.h"
#include <fstream>
#include <cassert>
#include <iostream> // std::cout
#include <sstream>
#include <numbers>
#include <vector>
#include <direct.h>

class LauncherScene :
    public SceneBase
{
public:
    LauncherScene();
    LauncherScene(SharingScenes* _sharingScenes, std::string workGuid);

    void Collide();
    void Update();
    void Draw();

private:
    CanvasObject* canvas;
    RectangleObject* bg;

    picojson::object obj;

    /* �Љ�p�I�u�W�F�N�g */
    ImageObject* thumbnail;
    TextObject* category;
    TextObject* title;
    TextObject* author;
    TextObject* guidText;
    TextObject* description;
    TextObject* photoGalleryText;
    CanvasObject* descriptionCanvas;
    CanvasObject* thumbnailCanvas;
    std::vector<LineObject*> descriptionLines;
    std::vector<ImageObject*> images;
    CanvasObject* imagesCanvas;

    ButtonObject* launch;

    RectangleObject* imageBackGround;

    /* �Љ�p�I�u�W�F�N�g */

    std::string guid;

    // buffer
    PosVec thumbnailPos;
    std::vector<PosVec> imagesPos;
    PosVec thumbnailSize;
    std::vector<PosVec> imagesSize;

    ImageObject* isBigImage;
    CanvasObject* isBigCanvas;
    PosVec* isBigPos;
    PosVec* isBigSize;

    const float maxImageLongLengthOnBig = 800.f;
    const float zoomFrame = .5f;
};

