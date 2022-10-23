#include "NoticeObject.h"

NoticeObject::NoticeObject()
{
	noticeFrame = new ButtonObject(
		PosVec(ApplicationPreference::GetBackgroundSize().x - 500.f, ApplicationPreference::GetBackgroundSize().y - 150.f),
		PosVec(450.f, 100.f), true, true);
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
		PosVec(ApplicationPreference::GetBackgroundSize().x - 90.f, ApplicationPreference::GetBackgroundSize().y - 140.f),
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
}

NoticeObject::~NoticeObject()
{
}

