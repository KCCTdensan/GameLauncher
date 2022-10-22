#pragma once
#include "SceneBase.h"
#include "OriginalObjects.h"
#include "SceneManager.h"
#include "MusicPlayer.h"
#include "PlayStateRotater.h"

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

    CanvasObject* canvas;

    RectangleObject* bg;

    PlayData* nowPlaying;

    TextObject* nextLabel;
    TextObject* nextTitle;
    TextObject* nextAuthor;

    TextObject* songTitle;
    TextObject* songAuthor;
    TextObject* songHandleName; // �n���h���ԍ��\��
    ButtonObject* startButton; // �������Ƃɉ摜�؂�ւ�
    ProgressObject* playBar;
    ProgressObject* volumeBar;
    ButtonObject* loopButton; // 

    PlayListObject* playListObject;
    InputObject* ideleteList;
    ButtonObject* bdeleteList;

    PlayStateRotater playStateRotater;
};

