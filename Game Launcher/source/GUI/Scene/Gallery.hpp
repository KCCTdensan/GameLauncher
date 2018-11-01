#pragma once

#include "Scene.hpp"
#include "../../ItemManager.hpp"
#include "../Window.hpp"
#include "../Button.hpp"
#include <vector>

#ifndef INCLUDE_GALLERY_HPP
#define INCLUDE_GALLERY_HPP


class item_button :public button
{
public:
	item_button(unsigned short Width, unsigned short Height);
	~item_button();
};

class gallery :public scene
{
	const int MenuWidth;
	const category Category;
	window MenuWindow;
	window PreviewWindow;

protected:
	button MainMenuButton;
	std::vector<item_info*> Items;
	std::vector<item_button*> Buttons;

	void CreateButtons();
	void DeleteButtons();
	void DrawBkgnd();

public:
	const static color ColorAccent[MAX_CATEGORY];

	gallery(scene_manager_interface *SceneChanger, category Category, unsigned short BmpWidth, unsigned short BmpHeight);
	~gallery();
};


#endif