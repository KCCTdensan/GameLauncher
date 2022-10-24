#include "NoticeCanvas.h"

NoticeCanvas::NoticeCanvas()
{
	NoticeObject* notice = new NoticeObject("通知機能の起動を確認しました。", "mplus20", "SETUP NOTICE");

	layer.AddObject(notice->GetNoticeFrame());
	layer.AddObject(notice->GetDeletedFrame());
	layer.AddObject(notice->GetTextObject());
	layer.AddObject(notice->GetTitleObject());

	notice->GetTextObject()->SetInnerColor(
		ColorPreset::textObject);
	notice->GetTitleObject()->SetInnerColor(
		ColorPreset::textObject);

	notices.push_back(notice);

}

void NoticeCanvas::UpdateAction()
{
	for (auto it = notices.begin(); it != notices.end(); ) {
		if (((*it)->GetDeletedFrame()->GetMouseSelected() || ((*it)->GetIsNoLife() && (int)(*it)->GetNoticeFrame()->GetPos().y == (int)(*it)->GetNoticeInitializePos().y)) && !(*it)->GetNoticeFrame()->GetMouseSelected()) {
			delete (*it)->GetDeletedFrame();
			delete (*it)->GetNoticeFrame();
			delete (*it)->GetTextObject();
			delete (*it)->GetTitleObject();
			layer.DeleteObject((*it)->GetDeletedFrame());
			layer.DeleteObject((*it)->GetNoticeFrame());
			layer.DeleteObject((*it)->GetTextObject());
			layer.DeleteObject((*it)->GetTitleObject());
			it = notices.erase(it);
			continue;
		}
		it++;
	}

	int i = 0;
	//clsDx();
	for (auto& item : notices) {
		item->GetNoticeFrame()->ChangeValueWithAnimation(&item->GetNoticeFrame()->GetVectorPointer(VectorType::POS)->y, item->GetNoticeInitializePos().y - item->GetNoticeFrame()->GetSize().y * (float)i, 1.f);
		item->GetTitleObject()->ChangeValueWithAnimation(&item->GetTitleObject()->GetVectorPointer(VectorType::POS)->y, item->GetNoticeInitializePos().y - item->GetNoticeFrame()->GetSize().y * (float)i, 1.f);
		item->GetDeletedFrame()->ChangeValueWithAnimation(&item->GetDeletedFrame()->GetVectorPointer(VectorType::POS)->y, item->GetNoticeInitializePos().y - item->GetNoticeFrame()->GetSize().y * (float)i, 1.f);
		item->GetTextObject()->ChangeValueWithAnimation(&item->GetTextObject()->GetVectorPointer(VectorType::POS)->y, item->GetNoticeInitializePos().y + item->GetTextOffset().y - item->GetNoticeFrame()->GetSize().y * (float)i, 1.f);
		item->GetTextObject()->CalcPos();
		item->GetTitleObject()->CalcPos();
		item->TimerUpdate();
		//printfDx("%d, %.2f, %.2f\n", i, item->GetNoticeFrame()->GetPos().y, notices[0]->GetNoticeFrame()->GetPos().y - item->GetNoticeFrame()->GetSize().y * (float)i);
		i++;
	}
}

void NoticeCanvas::MakeNotice(std::string text, std::string title)
{
	NoticeObject* notice = new NoticeObject(text, "mplus20", title);

	layer.AddObject(notice->GetNoticeFrame());
	layer.AddObject(notice->GetDeletedFrame());
	layer.AddObject(notice->GetTextObject());
	layer.AddObject(notice->GetTitleObject());

	notice->GetTextObject()->SetInnerColor(
		ColorPreset::textObject);
	notice->GetTitleObject()->SetInnerColor(
		ColorPreset::textObject);

	notices.push_back(notice);
}
