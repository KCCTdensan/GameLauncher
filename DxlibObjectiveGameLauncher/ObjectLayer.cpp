#include "ObjectLayer.h"

void ObjectLayer::AddObject(ObjectBase* _object)
{
	for (auto& item : layer) {
		if (item.object == _object) return;
	}
	layer.push_back(ObjectFunc(_object));
}

void ObjectLayer::DeleteObject(ObjectBase* _object)
{
	for (auto it = layer.begin(); it != layer.end(); it++) {
		if (it->object == _object) {
			layer.erase(it);
			break;
		}
	}
}

void ObjectLayer::Clear()
{
	layer.clear();
}

void ObjectLayer::SetTopLayer(ObjectBase* _object, int _shift)
{
	int i = 0;
	for (auto& item : layer) {
		if (item.object == _object) break;
		i++;
	}
	if (i == (int)layer.size()) return;

	for (int k = i; k < (int)layer.size() - 1; k++) {
		std::iter_swap(layer.begin() + k, layer.begin() + k + 1);
	}
	//std::iter_swap(--layer.end(), layer.begin() + i);
	//layer[layer.size() - 1] = _object;
}

void ObjectLayer::SetButtomLayer(ObjectBase* _object, int _shift)
{
	int i = 0;
	for (auto& item : layer) {
		if (item.object == _object) break;
		i++;
	}
	if (i == (int)layer.size()) return;

	for (int k = i; k > 0; k--) {
		std::iter_swap(layer.begin() + k, layer.begin() + k - 1);
	}

	//std::iter_swap(layer.begin(), layer.begin() + i);
}

void ObjectLayer::MoveLayer(ObjectBase* _object, int _distance)
{
}

void ObjectLayer::Collide()
{
	for (auto& item : layer) {
		item.object->Collide();
	}
}

void ObjectLayer::Update()
{
	for (auto& item : layer) {
		item.object->Update();
	}
}

void ObjectLayer::Draw()
{
	for (auto& item : layer) {
		item.object->Draw();
	}
}
