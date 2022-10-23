#include "NoticeCanvas.h"

NoticeCanvas::NoticeCanvas()
{
	//ButtonObject* button = new ButtonObject(
	//	PosVec(ApplicationPreference::GetBackgroundSize().x - 500.f, ApplicationPreference::GetBackgroundSize().y - 150.f),
	//	PosVec(450.f, 100.f), true, true);
	//button->SetInnerColor(
	//	ColorPreset::tileInner,
	//	ColorPreset::tileHovered,
	//	ColorPreset::tileClicked,
	//	ColorPreset::tileSelected);
	//button->SetOutlineColor(
	//	ColorPreset::tileOuterMouse,
	//	ColorPreset::tileOuterMouse,
	//	ColorPreset::tileOuterMouse,
	//	ColorPreset::tileOuterMouse, 3.f);
	//button->SetInnerAnimation(.15f);
	//button->SetOuterAnimation(.15f);

	//layer.AddObject(button);

	NoticeObject* notice = new NoticeObject();

	layer.AddObject(notice->GetNoticeFrame());
	layer.AddObject(notice->GetDeletedFrame());
	notices.push_back(notice);

}

void NoticeCanvas::UpdateAction()
{
	for (auto it = notices.begin(); it != notices.end(); ) {
		if ((*it)->GetDeletedFrame()->GetMouseSelected()) {
			delete (*it)->GetDeletedFrame();
			delete (*it)->GetNoticeFrame();
			it = notices.erase(it);
			continue;
		}
		it++;
	}
}
