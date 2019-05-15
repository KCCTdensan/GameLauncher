#pragma once

#include "../mem_dc.hpp"
#include "../task.hpp"

#ifndef INCLUDE_SCENE_HPP
#define INCLUDE_SCENE_HPP


class SceneChangerInterface;

class Scene : public MemDC, public Task
{
protected:
	SceneChangerInterface *SceneChanger;

public:
	Scene(HWND hWnd, SceneChangerInterface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	virtual int paint();
};


#endif