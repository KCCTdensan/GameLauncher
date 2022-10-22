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

    TextObject* songTitle;
    TextObject* songAuthor;
    TextObject* songHandleName; // ハンドル番号表示
    ButtonObject* startButton; // 押すごとに画像切り替え
    ProgressObject* playBar;
    ProgressObject* volumeBar;
    ButtonObject* loopButton; // 

    PlayListObject* playListObject;
    InputObject* ideleteList;
    ButtonObject* bdeleteList;

    PlayStateRotater playStateRotater;
};

