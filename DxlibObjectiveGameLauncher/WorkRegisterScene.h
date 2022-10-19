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
#include <sys/stat.h>
#include "UUIDGenerator.h"

class WorkRegisterScene :
    public SceneBase
{
public:
    WorkRegisterScene();
    WorkRegisterScene(SharingScenes* _sharingScenes);

    void Collide();
    void Update();
    void Draw();

private:

    RectangleObject* bg;

    picojson::object obj;

    std::string guid;

    // Category�{�^��������
    TextObject* titlename;

    TextObject* lWorkName;
    TextObject* lWorkAuthor;
    TextObject* lWorkDescription;
    InputObject* iWorkName;
    InputObject* iWorkAuthor;
    InputObject* iWorkDescription;

    TextObject* iguid;

    ButtonObject* openDirectoryButtton; // Open in
    ButtonObject* setThumbnailButtton; // �_�C�A���O���J��
    ButtonObject* setImagesButtton; // �_�C�A���O���J��
    ButtonObject* makeJsonDataButton; // picojson
};

