#pragma once

#include "Scene.hpp"
#include "../../ItemManager.hpp"
#include <vector>

#ifndef INCLUDE_GALLERY_HPP
#define INCLUDE_GALLERY_HPP


class item_button :public mem_dc
{
public:
	item_button(unsigned short Width, unsigned short Height);
	~item_button();
};

class gallery :public scene
{
	const int MenuWidth;

	mem_dc MenuDC;
	mem_dc PreviewDC;

protected:
	std::vector<item_info*> Items;
	std::vector<item_button*> Buttons;

	void DrawBkgnd();

public:
	const static color ColorAccent[MAX_CATEGORY];

	gallery(scene_manager_interface *SceneChanger, unsigned short BmpWidth, unsigned short BmpHeight);
	~gallery();
};


#endif