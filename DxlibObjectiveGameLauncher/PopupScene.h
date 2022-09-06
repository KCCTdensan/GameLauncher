#pragma once
#include "SceneBase.h"
#include "PopupWindow.h"
#include <vector>

class PopupScene :
    public SceneBase
{
public:
    PopupScene();
    PopupScene(SharingScenes* _sharingScenes);
    ~PopupScene() {}

    void Collide() override;
    void Update() override;
    void Draw() override;

private:
    std::vector<PopupWindow> popups;
};

