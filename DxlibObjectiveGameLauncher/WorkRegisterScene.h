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
#include <direct.h>
#include <sys/stat.h>
#include "UUIDGenerator.h"
#include <Windows.h>
#include <tchar.h>
#include "StringConvert.h"
#include <sys/stat.h>

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

    void ResetParams();
    void SetMiddleCenterText(ButtonObject* button);
    void SetDisplayText(TextObject* text, std::string* value);

    RectangleObject* bg;

    picojson::object obj;

    std::string guid;
    std::string path;
    std::string workerPath;
    std::string thumbnailPath;
    std::string imagesPath;
    std::vector<std::string> imagePathVector;

    // Categoryボタン未実装
    TextObject* titlename;

    TextObject* lWorkName;
    TextObject* lWorkAuthor;
    TextObject* lWorkCategory;
    TextObject* lWorkURL;
    TextObject* lWorkDescription;
    InputObject* iWorkName;
    InputObject* iWorkCategory;
    InputObject* iWorkURL;
    InputObject* iWorkAuthor;
    InputObject* iWorkDescription;

    TextObject* lExistingGUID;
    InputObject* iExistingGUID;
    

    TextObject* lguid;
    TextObject* lWorkPath;
    TextObject* lThumbPath;
    TextObject* lImagesPath;
    TextObject* dguid;
    TextObject* dWorkPath;
    TextObject* dThumbPath;
    TextObject* dImagesPath;

    ButtonObject* openDirectoryButtton; // Open in
    ButtonObject* setWorkerButtton; // ダイアログを開く
    ButtonObject* setThumbnailButtton; // ダイアログを開く
    ButtonObject* setImagesButtton; // ダイアログを開く
    ButtonObject* makeJsonDataButton; // picojson

    ButtonObject* clearButton;
    ButtonObject* deleteButton;
};

