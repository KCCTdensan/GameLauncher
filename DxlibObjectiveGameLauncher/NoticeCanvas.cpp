#include "NoticeCanvas.h"

NoticeCanvas::NoticeCanvas()
{
	NoticeObject* notice = new NoticeObject("通知機能の起動を確認しました。", "mplus20");

	layer.AddObject(notice->GetNoticeFrame());
	layer.AddObject(notice->GetDeletedFrame());
	layer.AddObject(notice->GetTextObject());

	notice->GetTextObject()->SetInnerColor(
		ColorPreset::textObject);

	notices.push_back(notice);

}

void NoticeCanvas::UpdateAction()
{
	for (auto it = notices.begin(); it != notices.end(); ) {
		if ((*it)->GetDeletedFrame()->GetMouseSelected() || (*it)->GetIsNoLife()) {
			delete (*it)->GetDeletedFrame();
			delete (*it)->GetNoticeFrame();
			layer.DeleteObject((*it)->GetDeletedFrame());
			layer.DeleteObject((*it)->GetNoticeFrame());
			layer.DeleteObject((*it)->GetTextObject());
			it = notices.erase(it);
			continue;
		}
		it++;
	}

	int i = 0;
	for (auto& item : notices) {
		item->GetNoticeFrame()->ChangeValueWithAnimation(&item->GetNoticeFrame()->GetVectorPointer(VectorType::POS)->y, notices[0]->GetNoticeFrame()->GetPos().y - item->GetNoticeFrame()->GetSize().y * (float)i, 1.f);
		item->TimerUpdate();
		i++;
	}
}

void NoticeCanvas::MakeNotice(std::string text)
{
	NoticeObject* notice = new NoticeObject(text, "mplus20");

	layer.AddObject(notice->GetNoticeFrame());
	layer.AddObject(notice->GetDeletedFrame());
	layer.AddObject(notice->GetTextObject());

	notice->GetTextObject()->SetInnerColor(
		ColorPreset::textObject);

	notices.push_back(notice);
}
