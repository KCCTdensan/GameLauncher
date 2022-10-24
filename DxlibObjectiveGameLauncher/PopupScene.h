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

    void MakeNotice(std::string text, std::string title = "NOTICE");

private:
    std::vector<PopupWindow> popups;

    MusicCanvas* musicCanvas;
    NoticeCanvas* noticeCanvas;
    PopupWindow popupMusic;
    PopupWindow popupNotice;
};

