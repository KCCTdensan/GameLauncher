#pragma once

#include "../MemDC.hpp"
#include "../Task.hpp"
#include "../SceneChangerInterface.hpp"

#ifndef INCLUDE_SCENE_HPP
#define INCLUDE_SCENE_HPP


class Scene : public MemDC, public Task
{
protected:
	SceneChangerInterface *SceneChanger;

public:
	Scene(SceneChangerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	virtual int Paint(HWND hWnd);
};


#endif