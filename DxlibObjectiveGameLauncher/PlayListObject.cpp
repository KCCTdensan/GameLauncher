#include "PlayListObject.h"

void PlayListObject::Collide()
{
	CollideMouseAsBox();

	for (auto& item : buttons) {
		item->Collide();
	}
}

void PlayListObject::Update()
{
	CheckGUID();
	UpdateEnforcedMouseCollision();

	mouseHoveringIndex = -1;
	mouseClickingIndex = -1;
	mouseSelectingIndex = -1;
	int i = 0;
	for (auto& item : buttons) {
		if (item->GetMouseHit())
			mouseHoveringIndex = i;
		if (item->GetMouseClicked())
			mouseClickingIndex = i;
		if (item->GetMouseSelected())
			mouseSelectingIndex = i;
		i++;
	}

	SetAnimationColorPoint(&innerAnimation, innerAnimation.current, innerColor);
	SetAnimationColorPoint(&outerAnimation, outerAnimation.current, outerColor);
	SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)innerColor.a);
	SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)outerColor.a);

	if (!enabled) {
		SetAnimationColorPoint(&innerAnimation, innerAnimation.current, listDisabledInnerColor);
		SetAnimationColorPoint(&outerAnimation, outerAnimation.current, listDisabledOuterColor);
		SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current, (float)listDisabledInnerColor.a);
		SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current, (float)listDisabledOuterColor.a);
	}

	UpdateAnimationColor(&innerAnimation);
	UpdateAnimationColor(&outerAnimation);
	UpdateAnimation(&innerAlphaAnimation);
	UpdateAnimation(&outerAlphaAnimation);
	UpdateAnimation(&imageAlphaAnimation); // ‰æ‘œalpha’l

	UpdatePointerAnimation();

	for (auto& item : buttons) {
		item->Update();
	}
}

void PlayListObject::Draw()
{
	if (canvasId != -1) {
		SetDrawScreen(canvasId);
	}
	else {
		SetDrawScreen(DX_SCREEN_BACK);
	}
	SetDrawArea((int)pos.x, (int)pos.y, (int)(pos.x + size.x + 1), (int)(pos.y + size.y + 1));
	if (listEnabledFill) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)innerAlphaAnimation.current);
		int resultInnerColor = innerAnimation.current.Get();
		//DrawBoxAA(pos.x + outlineWidth, pos.y + outlineWidth, pos.x + size.x - outlineWidth + 1, pos.y + size.y - outlineWidth + 1, resultInnerColor, true, 0);
		DrawBoxAA(pos.x, pos.y, pos.x + size.x + 1, pos.y + size.y + 1, resultInnerColor, true, 0);
	}

	DrawImage();

	for (auto& item : buttons) {
		item->Draw();
	}

	if (canvasId != -1) {
		SetDrawScreen(canvasId);
	}
	else {
		SetDrawScreen(DX_SCREEN_BACK);
	}
	if (listEnabledOutline) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)outerAlphaAnimation.current);
		int resultOuterColor = outerAnimation.current.Get(); // debug
		float offset = listOutlineWidth / 2;
		DrawLineAA(pos.x + offset, pos.y + offset, pos.x + size.x - offset + 1, pos.y + offset, resultOuterColor, listOutlineWidth);
		DrawLineAA(pos.x + size.x - offset, pos.y + offset, pos.x + size.x - offset, pos.y + size.y - offset + 1, resultOuterColor, listOutlineWidth);
		DrawLineAA(pos.x + size.x - offset, pos.y + size.y - offset, pos.x + offset - 1, pos.y + size.y - offset, resultOuterColor, listOutlineWidth);
		DrawLineAA(pos.x + offset, pos.y + size.y - offset, pos.x + offset, pos.y + offset - 1, resultOuterColor, listOutlineWidth);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	SetDrawArea(0, 0, (int)ApplicationPreference::GetBackgroundSize().x, (int)ApplicationPreference::GetBackgroundSize().y);

	SetDrawScreen(DX_SCREEN_BACK);
}

bool PlayListObject::SetList(std::vector<PlayData> playLists, std::string fontName, PosVec textOffset)
{
	if (listSample == nullptr) listSample = new ButtonObject();
	if (this->lists.size() == playLists.size()) return false;
	lists = playLists;
	for (auto& item : buttons) {
		delete item;
	}
	buttons.clear();
	children.clear();
	int i = 0;
	for (auto& item : lists) {
		ButtonObject* button = new ButtonObject(
			PosVec(pos.x, pos.y + i * listHeight), PosVec(size.x, listHeight), true, true);
		button->SetInnerColor(
			*listSample->GetColor(ColorType::INNER),
			*listSample->GetColor(ColorType::HOVERED),
			*listSample->GetColor(ColorType::CLICKED),
			*listSample->GetColor(ColorType::SELECTED));
		button->SetOutlineColor(
			*listSample->GetColor(ColorType::OUTER_INNER),
			*listSample->GetColor(ColorType::OUTER_HOVERED),
			*listSample->GetColor(ColorType::OUTER_CLICKED),
			*listSample->GetColor(ColorType::OUTER_SELECTED), 2.f);
		button->SetupText(fontName, std::to_string(i) + ": " + item.title + "\n" + item.author, Color255(0, 0, 0, 150));
		button->GetTextObject()->Move(textOffset);
		buttons.push_back(button);
		RegisterChildren(button);
		i++;
	}

	SetSize(PosVec(size.x, listSample->GetSize().y * buttons.size()));

	return true;
}

void PlayListObject::SetMouseOffIndex()
{
	for (auto& item : buttons) {
		item->SetMouseOff();
	}
}