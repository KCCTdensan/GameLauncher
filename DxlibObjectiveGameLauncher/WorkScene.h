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

    /* �Љ�p�I�u�W�F�N�g */
    ImageObject thumbnail;


    /* �Љ�p�I�u�W�F�N�g */

    std::string guid;
};

