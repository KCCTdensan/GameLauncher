#pragma once
#include "SceneBase.h"
#include "PopupWindow.h"
#include "MusicCanvas.h"
#include "NoticeCanvas.h"
#include <vector>

class PopupScene :
    public SceneBase
{
public:
    PopupScene();
    ~PopupScene() {}

    void Collide() override;
    void Update() override;
    void Draw() override;

private:
    std::vector<PopupWindow> popups;

    MusicCanvas* musicCanvas;
    NoticeCanvas* noticeCanvas;
    PopupWindow popupMusic;
    PopupWindow popupNotice;
};

