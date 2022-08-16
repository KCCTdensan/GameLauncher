#pragma once
#include "ObjectBase.h"
#include "ObjectFuncData.h"
#include <vector>
class ObjectLayer
{
public:
	ObjectLayer() {}
	~ObjectLayer() {}

	void AddObject(ObjectBase* _object);
	void DeleteObject(ObjectBase* _object);

	void SetTopLayer(ObjectBase* _object,int _shift = 0);
	void SetButtomLayer(ObjectBase* _object,int _shift = 0);

	void MoveLayer(ObjectBase* _object, int _distance);
	
	int Total() { return (int)layer.size(); }

	void Collide();
	void Update();
	void Draw();

private:
	std::vector<ObjectFunc> layer;
};