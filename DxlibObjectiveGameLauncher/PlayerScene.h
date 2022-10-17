#pragma once
#include "SceneBase.h"
#include "OriginalObjects.h"
#include "SceneManager.h"
#include "MusicPlayer.h"

class PlayerScene :
    public SceneBase
{
public:
    PlayerScene();
    PlayerScene(SharingScenes* _sharingScenes);
    ~PlayerScene();

    void Collide();
    void Update();
    void Draw();

private:

    RectangleObject* bg;

    PlayData* nowPlaying;

    TextObject* songTitle;
    TextObject* songAuthor;
    TextObject* songHandleName; // �n���h���ԍ��\��
    ButtonObject* startButton; // �������Ƃɉ摜�؂�ւ�
    ProgressObject* playBar;
    ButtonObject* loopButton; // 
};
