#pragma once
#include "SceneBase.h"
#include "OriginalObjects.h"
#include "SceneManager.h"

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

    TextObject* songTitle;
    TextObject* songAuthor;
    TextObject* songHandleName; // ƒnƒ“ƒhƒ‹”Ô†•\¦
    ButtonObject* startButton; // ‰Ÿ‚·‚²‚Æ‚É‰æ‘œØ‚è‘Ö‚¦
    ProgressObject* playBar;
};

