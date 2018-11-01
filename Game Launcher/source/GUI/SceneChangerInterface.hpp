#pragma once

#include <Windows.h>

#ifndef INCLUDE_SCENECHANGERINTERFACE_HPP
#define INCLUDE_SCENECHANGERINTERFACE_HPP


enum scene_name
{
	SceneName_MainMenu,
	SceneName_AppGallery,
	SceneName_GameGallery,
	SceneName_MusicGallery,
	SceneName_PictureGallery,
	SceneName_3DModelGallery,
	SceneName_VideoGallery,
	SceneName_OthersGallery,

	NumSceneName
};

class scene_manager_interface
{
public:

};


#endif