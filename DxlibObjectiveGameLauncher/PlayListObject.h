#pragma once
#include "ObjectBase.h"
#include <vector>
#include "PlayData.h"
#include "ButtonObject.h"

// ���N���X�̃��\�b�h�͈ꕔ���������삵�Ȃ��\��������
class PlayListObject :
    public ObjectBase
{
public:
    PlayListObject(PosVec _pos, PosVec _size)
        : ObjectBase(_pos, _size), listSample(nullptr),
        listInnerColor(0), listOuterColor(0), listDisabledInnerColor(0), listDisabledOuterColor(0),
        listEnabledFill(true), listEnabledOutline(true), listOutlineWidth(false), listHeight(50.f)
    {}

    PlayListObject()
    {}

    // �F�L����������
    bool SetEnabledListFill(bool _enabled) { listEnabledFill = _enabled; return true; }
    bool SetEnabledListFill() { return listEnabledFill; }
    bool SetEnabledListOutline(bool _enabled, float _outlineWidth = -1.f) { listEnabledOutline = _enabled; listOutlineWidth = _outlineWidth ? _outlineWidth <= 0.f : 0.f; return true; }
    // ����p���^�[��
    bool SetEnabledListOutline() { return listEnabledOutline; }

    // �F���o�^��
    bool SetInnerColor(Color255 _innerColor, bool _defaultFill = true)
    {
        innerColor = _innerColor;
        if (_defaultFill) {
            innerAnimation.current = innerColor;
            innerAlphaAnimation.current = (float)innerColor.a;
        }
        listDisabledInnerColor = Color255(innerColor.r, innerColor.g, innerColor.b, (int)(innerColor.a / 5));
        return true;
    }
    // �A�E�g���C����\������ۂ�true�ɂȂ��Ă��邩���`�F�b�N
    bool SetOutlineColor(Color255 _outerColor, float _outlineWidth, bool _defaultFill = true) {
        outerColor = _outerColor;
        listOutlineWidth = _outlineWidth;
        if (_defaultFill) {
            outerAnimation.current = outerColor;
            outerAlphaAnimation.current = (float)outerColor.a;
        }
        listDisabledOuterColor = Color255(outerColor.r, outerColor.g, outerColor.b, (int)(outerColor.a / 5));
        return true;
    }

    ButtonObject* GetButtonListSample() { return listSample; }
    ButtonObject* SetButtonListSample(ButtonObject* sample) { listSample = sample; }

    bool SetListHeight(float _height) { listHeight = _height; return false; }

    bool SetList(std::vector<PlayData> playLists);

    // �X�V�`��
    void Collide() override;
    void Update() override;
    void Draw() override;

private:

    void CollideMouse() override {}

private:

    Color255 listInnerColor;
    Color255 listOuterColor;

    Color255 listDisabledInnerColor;
    Color255 listDisabledOuterColor;

    Color255 innerColor;
    Color255 outerColor;

    float listOutlineWidth;

    bool listEnabledFill;
    bool listEnabledOutline;

    float listHeight;

    ButtonObject* listSample;

    std::vector<PlayData> lists;
    std::vector<ButtonObject*> buttons;
};

