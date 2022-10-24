#pragma once
#include "ButtonObject.h"
#include "ColorPreset.h"

class NoticeObject
{
public:
	NoticeObject(std::string text, std::string handlename);
	~NoticeObject();

	ButtonObject* GetNoticeFrame() { return noticeFrame; }
	ButtonObject* GetDeletedFrame() { return deleteButton; }
	TextObject* GetTextObject() { return noticeText; }

	PosVec GetNoticeInitializePos() { return noticeInitializePos; }
	PosVec GetTextOffset() { return textOffset; }

	void TimerUpdate();

	bool GetIsNoLife() { return isNoLife; }

private:
	ButtonObject* noticeFrame;
	ButtonObject* deleteButton;
	TextObject* noticeText;

	bool isNoLife;

	PosVec textOffset;
	PosVec noticeSize;
	PosVec noticeInitializePos;

	float timeValue;
	float lifeMaxRemain;
};
