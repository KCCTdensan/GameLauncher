#include "scene_manager.hpp"
#include "Scene/main_menu.hpp"
#include "Scene/app_gallery.hpp"
#include "Scene/game_gallery.hpp"
#include "Scene/music_gallery.hpp"
#include "Scene/picture_gallery.hpp"
#include "Scene/model_gallery.hpp"
#include "Scene/video_gallery.hpp"
#include "Scene/others_gallery.hpp"


SceneManager::SceneManager(HWND hWnd, SceneName firstScene, unsigned short bmpWidth, unsigned short bmpHeight)
	: Task(hWnd)
{
	scenes[SceneName_MainMenu] = new MainMenu(hWnd, this, bmpWidth, bmpHeight);
	scenes[SceneName_AppGallery] = new AppGallery(hWnd, this, bmpWidth, bmpHeight);
	scenes[SceneName_GameGallery] = new GameGallery(hWnd, this, bmpWidth, bmpHeight);
	scenes[SceneName_MusicGallery] = new MusicGallery(hWnd, this, bmpWidth, bmpHeight);
	scenes[SceneName_PictureGallery] = new PictureGallery(hWnd, this, bmpWidth, bmpHeight);
	scenes[SceneName_3DModelGallery] = new ModelGallery(hWnd, this, bmpWidth, bmpHeight);
	scenes[SceneName_VideoGallery] = new VideoGallery(hWnd, this, bmpWidth, bmpHeight);
	scenes[SceneName_OthersGallery] = new OthersGallery(hWnd, this, bmpWidth, bmpHeight);
	currentScene = scenes[firstScene];
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < numScene; i++)
	{
		delete scenes[i];
		scenes[i] = nullptr;
	}
	currentScene = nullptr;
}

int SceneManager::initialize()
{
	return currentScene->initialize();
}

int SceneManager::finalize()
{
	return currentScene->finalize();
}

int SceneManager::paint()
{
	return currentScene->paint();
}

int SceneManager::mouseMove(unsigned short x, unsigned short y, unsigned int param)
{
	return currentScene->mouseMove(x, y, param);
}

int SceneManager::buttonLDown(unsigned short x, unsigned short y)
{
	return currentScene->buttonLDown(x, y);
}

int SceneManager::buttonLUp(unsigned short x, unsigned short y)
{
	return currentScene->buttonLUp(x, y);
}

int SceneManager::buttonRDown(unsigned short x, unsigned short y)
{
	return currentScene->buttonRDown(x, y);
}

int SceneManager::buttonRUp(unsigned short x, unsigned short y)
{
	return currentScene->buttonRUp(x, y);
}

int SceneManager::update()
{
	return currentScene->update();
}

int SceneManager::changeScene(SceneName nextScene)
{
	int ret = currentScene->finalize();
	if(ret != 0)
	{
		return ret;
	}
	currentScene = scenes[nextScene];
	return currentScene->initialize();
}