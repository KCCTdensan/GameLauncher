#pragma once
#include "SceneBase.h"
#include "OriginalObjects.h"
#include "SceneManager.h"
// îCà”ì«çû

#include "LauncherScene.h"

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

    CanvasObject* imagesCanvas;
    RectangleObject* imageBackGround;

    picojson::object welcome;

    PosVec iconPos;
    PosVec iconSize;
};

