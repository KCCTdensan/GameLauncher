#pragma once
#include "ButtonObject.h"
#include "ColorPreset.h"

class NoticeObject
{
public:
	NoticeObject();
	~NoticeObject();

	ButtonObject* GetNoticeFrame() { return noticeFrame; }
	ButtonObject* GetDeletedFrame() { return deleteButton; }

private:
	ButtonObject* noticeFrame;
	ButtonObject* deleteButton;
};
