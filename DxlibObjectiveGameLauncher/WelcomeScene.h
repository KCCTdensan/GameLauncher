#pragma once
#include "SceneBase.h"
#include "OriginalObjects.h"
#include "SceneManager.h"
// îCà”ì«çû
#include "PlayerScene.h"
#include "LauncherScene.h"
#include "ExePath.h"
#include "WorkRegisterScene.h"
#include "ImageChest.h"
#include <random>

class WelcomeScene :
    public SceneBase
{
public:
    WelcomeScene();
    WelcomeScene(SharingScenes* _sharingScenes);

    void Collide();
    void Update();
    void Draw();

private:
    CanvasObject* canvas;
    RectangleObject* bg;

    ImageObject* icon;
    ButtonObject* whatis;
    ButtonObject* organization;
    ButtonObject* gotoHome;
    ButtonObject* openURL;
    ImageObject* qrcode;
    ButtonObject* jumpToMusic;
    ButtonObject* jumpToWorkMan;

    ButtonObject* jumpTorandomPage;
    ButtonObject* rankButton;
    ButtonObject* jumpToNo1;
    ButtonObject* jumpToNo2;
    ButtonObject* jumpToNo3;

    CanvasObject* imagesCanvas;
    RectangleObject* imageBackGround;

    picojson::object welcome;

    PosVec iconPos;
    PosVec iconSize;
};

