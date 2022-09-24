#pragma once
#include "ObjectBase.h"
#include <vector>
#include "PlayData.h"

// ���N���X�̃��\�b�h�͈ꕔ���������삵�Ȃ��\��������
class PlayListObject :
    public ObjectBase
{
    PlayListObject(PosVec _pos, PosVec _size)
    {}

    PlayListObject()
    {}

    // �F�L����������
    bool SetEnabledListFill(bool _enabled) { listEnabledFill = _enabled; return true; }
    bool SetEnabledListFill() { return listEnabledFill; }
    bool SetEnabledListOutline(bool _enabled, float _outlineWidth = -1.f) { listEnabledOutline = _enabled; listOutlineWidth = _outlineWidth ? _outlineWidth <= 0.f : 0.f; return true; }
    // ����p���^�[��
    bool SetEnabledListOutline() { return listEnabledOutline; }

private:
    Color255 listInnerColor;
    Color255 listOuterColor;

    Color255 listDisabledInnerColor;
    Color255 listDisabledOuterColor;

    float listOutlineWidth;

    bool listEnabledFill;
    bool listEnabledOutline;

    std::vector<PlayData*> lists;
};

