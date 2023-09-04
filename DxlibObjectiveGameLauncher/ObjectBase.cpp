#include "ObjectBase.h"

ObjectBase::~ObjectBase()
{
	DeleteGraph(imageHandle);
}

void ObjectBase::UpdateEnforcedMouseCollision()
{
	if (enforcedHovered) {
		enforcedHovered = false;
		mouseHit = true;
	}
	if (enforcedClicked) {
		enforcedClicked = false;
		mouseClicked = true;
	}
	if (enforcedSelected) {
		enforcedClicked = false;
		mouseSelected = true;
	}
}

void ObjectBase::SetAnimationColorPoint(AnimationColorStatus* type, Color255 _start, Color255 _goal)
{
	type->elapsedTime = 0.f;

	type->start = _start;
	if (type->end.r != _goal.r &&
		type->end.g != _goal.g &&
		type->end.b != _goal.b) type->durationRemain = type->duration;
	type->end = _goal;
	type->current = _start;

	if (type->durationRemain <= 0.f || !type->animationEnabled) {
		type->current = type->end;
		return;
	}

	type->m[0] = (type->end.r - type->start.r) / type->durationRemain;
	type->m[1] = (type->end.g - type->start.g) / type->durationRemain;
	type->m[2] = (type->end.b - type->start.b) / type->durationRemain;
}

void ObjectBase::UpdateAnimationColor(AnimationColorStatus* type)
{
	if (type->animationEnabled) {

		type->durationRemain -= ApplicationTime::DeltaTime();

		type->elapsedTime += ApplicationTime::DeltaTime();
		if (type->elapsedTime >= type->duration || type->durationRemain <= 0.f) {
			type->elapsedTime = type->duration;
			type->durationRemain = type->duration;
		}
		else {
			type->current = Color255(
				(int)(type->m[0] * type->elapsedTime + type->start.r),
				(int)(type->m[1] * type->elapsedTime + type->start.g),
				(int)(type->m[2] * type->elapsedTime + type->start.b));
		}
	}
}

void ObjectBase::SetAnimationPoint(AnimationStatus* type, float _start, float _goal)
{
	type->elapsedTime = 0.f;

	type->start = _start;
	if (type->end != _goal) {
		//printfDx("\n");
		type->durationRemain = type->duration;
	}
	type->end = _goal;
	type->current = _start;

	if (type->durationRemain <= 0.f || !type->animationEnabled) {
		type->current = type->end;
		return;
	}
	type->m = (type->end - type->start) / type->durationRemain;

}

void ObjectBase::UpdateAnimation(AnimationStatus* type)
{
	if (type->animationEnabled) {

		type->durationRemain -= ApplicationTime::DeltaTime();

		type->elapsedTime += ApplicationTime::DeltaTime();
		if (type->elapsedTime >= type->duration || type->durationRemain <= 0.f) {
			type->elapsedTime = type->duration;
			type->current += type->m * type->elapsedTime;

		}
		else {
			type->current += type->m * type->elapsedTime;
		}
		if (type->m < 0 && type->current <= type->end) type->current = type->end;
		else if (type->m > 0 && type->current >= type->end) type->current = type->end;
	}
}

void ObjectBase::UpdatePointerAnimation()
{
	for (auto it = pColorAnimation.begin(); it != pColorAnimation.end(); it++) {
		UpdateAnimationColor(&(it->animation));
		*(it->color) = it->animation.current;
	}
	for (auto it = pAnimation.begin(); it != pAnimation.end(); it++) {
		UpdateAnimation(&(it->animation));
		*(it->value) = it->animation.current;
		//printfDx("%.3f elapsed:%.3f\n", it->animation.m, it->animation.elapsedTime);
	}
	for (auto it = pAnimationInt.begin(); it != pAnimationInt.end(); it++) {
		UpdateAnimation(&(it->animation));
		*(it->value) = (int)it->animation.current;
		//printfDx("%.3f elapsed:%.3f\n", it->animation.m, it->animation.elapsedTime);
	}
}

void ObjectBase::CollideMouseAsBox()
{
	if (!enabled) return;
	bool beforeMouseClicked = mouseClicked;
	bool goSelecting = false;

	bool pFlag = true;
	if (parent != nullptr) pFlag = parent->GetMouseHit();

	PosVec offset = PosVec();
	bool clickExpanded = Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) >= PressFrame::FIRST ? true : false;
	if (clickExpanded && expandedNum && mouseClicked) {
		offset.x = ApplicationPreference::GetBackgroundSize().x / 6.f;
		offset.y = ApplicationPreference::GetBackgroundSize().y / 6.f;
	}

	if (pos.x - offset.x <= Input::MouseInput::GetMouse().x &&
		pos.x + size.x + offset.x >= Input::MouseInput::GetMouse().x &&
		pos.y - offset.y <= Input::MouseInput::GetMouse().y &&
		pos.y + size.y + offset.y >= Input::MouseInput::GetMouse().y && pFlag) {

		mouseHit = true;

		// オブジェクトの重複判定登録処理

		ObjectOverlapping::UpdateObject(this, enforcedCollision);

		if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) >= PressFrame::FIRST) {
			if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) == PressFrame::FIRST)
				mouseClicked = true;
		}
		else {
			if (pos.x <= Input::MouseInput::GetMouse().x &&
				pos.x + size.x >= Input::MouseInput::GetMouse().x &&
				pos.y <= Input::MouseInput::GetMouse().y &&
				pos.y + size.y >= Input::MouseInput::GetMouse().y && pFlag) {
				mouseClicked = false;
				goSelecting = true;
			}
		}
	}
	else {
		mouseHit = false;

		if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) >= PressFrame::FIRST && !mouseClicked) {
			mouseSelected = false;
		}
	}

	if (Input::MouseInput::GetClick(MOUSE_INPUT_LEFT) == PressFrame::ZERO)
		mouseClicked = false;

	if (beforeMouseClicked && !mouseClicked && goSelecting) {
		mouseSelected = true;
	}

	beCalledNoMouse = false;
}

void ObjectBase::DrawImage()
{
	if (imageHandle != -1) {
		PosVec originalImageSize;
		GetGraphSizeF(imageHandle, &originalImageSize.x, &originalImageSize.y);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)imageAlphaAnimation.current);
		SetDrawArea((int)pos.x, (int)pos.y, (int)(pos.x + size.x + 1), (int)(pos.y + size.y + 1));
		DrawRotaGraph3F(
			pos.x + imageOffset.x,
			pos.y + imageOffset.y,
			imageCenter.x, imageCenter.y,
			(double)(imageSize.x / originalImageSize.x),
			(double)(imageSize.y / originalImageSize.y),
			imageAngle, imageHandle, true, imageTurnFlagX, imageTurnFlagY);
	}
}

PosVec ObjectBase::GetLocalPos()
{
	if (parent != nullptr) {
		PosVec result;
		result.x = pos.x - parent->GetPos().x;
		result.y = pos.y - parent->GetPos().y;
		result.z = pos.z - parent->GetPos().z;
		return result;
	}
	return pos;
}

void ObjectBase::ChangeColorWithAnimation(Color255* pColor, Color255* endColor, float duration)
{
	for (auto it = pColorAnimation.begin(); it != pColorAnimation.end(); it++) {
		if (it->color == pColor) {
			if (it->animation.end.r == endColor->r &&
				it->animation.end.g == endColor->g &&
				it->animation.end.b == endColor->b) return;
			else {
				pColorAnimation.erase(it);
				break;
			}
		}
	}

	AnimationColorPointer* p = new AnimationColorPointer(
		AnimationColorStatus(),
		pColor
	);
	p->animation.animationEnabled = true;
	p->animation.duration = duration;
	p->animation.durationRemain = duration;
	p->animation.elapsedTime = 0.f;
	SetAnimationColorPoint(&(p->animation), *pColor, *endColor);
	pColorAnimation.push_back(*p);
}

void ObjectBase::ChangeValueWithAnimation(float* pValue, float endValue, float duration)
{
	for (auto it = pAnimation.begin(); it != pAnimation.end(); it++) {
		if (it->value == pValue) {
			if ((int)(it->animation.end) == (int)endValue) return;
			else {
				pAnimation.erase(it);
				break;
			}
		}
	}

	AnimationPointer* p = new AnimationPointer(
		AnimationStatus(),
		pValue
	);
	p->animation.animationEnabled = true;
	p->animation.duration = duration;
	p->animation.durationRemain = duration;
	p->animation.elapsedTime = 0.f;
	SetAnimationPoint(&(p->animation), *pValue, endValue);
	pAnimation.push_back(*p);
}

void ObjectBase::ChangeValueWithAnimation(int* pValue, int endValue, float duration)
{
	for (auto it = pAnimationInt.begin(); it != pAnimationInt.end(); it++) {
		if (it->value == pValue) {
			if ((int)(it->animation.end) == (int)endValue) return;
			else {
				pAnimationInt.erase(it);
				break;
			}
		}
	}

	AnimationPointerInt* p = new AnimationPointerInt(
		AnimationStatus(),
		pValue
	);
	p->animation.animationEnabled = true;
	p->animation.duration = duration;
	p->animation.durationRemain = duration;
	p->animation.elapsedTime = 0.f;
	SetAnimationPoint(&(p->animation), (float)*pValue, (float)endValue);
	pAnimationInt.push_back(*p);
}

void ObjectBase::SetCanvasId(int id)
{
	canvasId = id;

	// 子要素にも適用
	for (int i = 0; i < children.size(); i++) {
		children[i]->SetCanvasId(id);
	}
}

void ObjectBase::SetLocalPos(PosVec _localPos)
{
	if (parent != nullptr) {
		pos.x = parent->GetPos().x + _localPos.x;
		pos.y = parent->GetPos().y + _localPos.y;
		pos.z = parent->GetPos().z + _localPos.z;
	}
	else {
		pos = _localPos;
	}
}

bool ObjectBase::Move(PosVec _delta, bool _involvedParent)
{
	if (_involvedParent)
		pos = PosVec(pos.x + _delta.x, pos.y + _delta.y);

	// 子要素にも適用
	for (int i = 0; i < children.size(); i++) {
		children[i]->Move(_delta);
	}
	return true;
}

bool ObjectBase::RegisterChildren(ObjectBase* _object)
{
	//children.push_back(_object);
	for (auto& item : children) {
		if (item == _object) return false;
	}
	children.insert(children.end(), _object);
	return true;
}

bool ObjectBase::RegisterParent(ObjectBase* _object)
{
	parent = _object;
	for (int i = 0; i < children.size(); i++) {
		children[i]->RegisterParent(_object);
	}
	return true;
}
