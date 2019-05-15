#pragma once

#ifndef INCLUDE_SCENECHANGERINTERFACE_HPP
#define INCLUDE_SCENECHANGERINTERFACE_HPP


enum SceneName
{
	SceneName_MainMenu,
	SceneName_AppGallery,
	SceneName_GameGallery,
	SceneName_MusicGallery,
	SceneName_PictureGallery,
	SceneName_3DModelGallery,
	SceneName_VideoGallery,
	SceneName_OthersGallery,

	numScene
};

class SceneChangerInterface
{
public:
	virtual int changeScene(SceneName nextScene) = 0;
};


#endif