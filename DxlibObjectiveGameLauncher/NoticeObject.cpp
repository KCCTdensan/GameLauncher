#include "NoticeObject.h"

NoticeObject::NoticeObject(std::string text, std::string handlename)
	: lifeMaxRemain(5.f)
{
	timeValue = lifeMaxRemain;
	isNoLife = false;

	textOffset = PosVec(20, 40);
	noticeSize = PosVec(450.f, 100.f);
	noticeInitializePos = PosVec(ApplicationPreference::GetBackgroundSize().x - 500.f, ApplicationPreference::GetBackgroundSize().y - 150.f);

	noticeFrame = new ButtonObject(
		noticeInitializePos,
		noticeSize, true, true);
	noticeFrame->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	noticeFrame->SetOutlineColor(
		ColorPreset::tileOuterMouse,
		ColorPreset::tileOuterMouse,
		ColorPreset::tileOuterMouse,
		ColorPreset::tileOuterMouse, 2.f);
	noticeFrame->SetInnerAnimation(.15f);
	noticeFrame->SetOuterAnimation(.15f);

	deleteButton = new ButtonObject(
		PosVec(noticeInitializePos.x + noticeSize.x - 30.f, noticeInitializePos.y),
		PosVec(30.f, 30.f), true, true);
	deleteButton->SetInnerColor(
		ColorPreset::tileInner,
		ColorPreset::tileHovered,
		ColorPreset::tileClicked,
		ColorPreset::tileSelected);
	deleteButton->SetOutlineColor(
		ColorPreset::tileOuterMouse,
		ColorPreset::tileOuterMouse,
		ColorPreset::tileOuterMouse,
		ColorPreset::tileOuterMouse, 1.f);
	deleteButton->SetInnerAnimation(.15f);
	deleteButton->SetOuterAnimation(.15f);

	noticeFrame->RegisterChildren(deleteButton);

	noticeFrame->ChangeValueWithAnimation(&timeValue, 0.f, lifeMaxRemain * 20.f);

	noticeText = new TextObject(
		PosVec(noticeInitializePos.x + textOffset.x, noticeInitializePos.y + textOffset.y),
		PosVec(), handlename, text);
	noticeText->SetMaxWidth((int)(noticeSize.x - 2 * textOffset.x));
}

NoticeObject::~NoticeObject()
{
}

void NoticeObject::TimerUpdate()
{
	if (timeValue <= 0.f)
		isNoLife = true;
	//printfDx("%.3f, %.3f\n", lifeMaxRemain, timeValue);
}

