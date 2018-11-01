#include "SceneManager.hpp"
#include "Scene/MainMenu.hpp"
#include "Scene/AppGallery.hpp"
#include "Scene/GameGallery.hpp"
#include "Scene/MusicGallery.hpp"
#include "Scene/PictureGallery.hpp"
#include "Scene/ModelGallery.hpp"
#include "Scene/VideoGallery.hpp"
#include "Scene/OthersGallery.hpp"


scene_manager::scene_manager(HWND hWnd, scene_name FirstScene, unsigned short BmpWidth, unsigned short BmpHeight)
{
	Scenes[SceneName_MainMenu] = new main_menu(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_AppGallery] = new app_gallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_GameGallery] = new game_gallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_MusicGallery] = new music_gallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_PictureGallery] = new picture_gallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_3DModelGallery] = new model_gallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_VideoGallery] = new video_gallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_OthersGallery] = new others_gallery(hWnd, this, BmpWidth, BmpHeight);
	CurrentScene = Scenes[FirstScene];
}

scene_manager::~scene_manager()
{
	for (int i = 0; i < NumSceneName; i++)
	{
		delete Scenes[i];
		Scenes[i] = nullptr;
	}
	CurrentScene = nullptr;
}

int scene_manager::Initialize(HWND hWnd)
{
	return CurrentScene->Initialize(hWnd);
}

int scene_manager::Finalize(HWND hWnd)
{
	return CurrentScene->Finalize(hWnd);
}

int scene_manager::Paint(HWND hWnd)
{
	return CurrentScene->Paint(hWnd);
}

int scene_manager::MouseMove(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return CurrentScene->MouseMove(hWnd, wp, lp);
}

int scene_manager::LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return CurrentScene->LButtonDown(hWnd, wp, lp);
}

int scene_manager::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return CurrentScene->LButtonUp(hWnd, wp, lp);
}

int scene_manager::RButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return CurrentScene->RButtonDown(hWnd, wp, lp);
}

int scene_manager::RButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return CurrentScene->RButtonUp(hWnd, wp, lp);
}

int scene_manager::Update(HWND hWnd)
{
	return CurrentScene->Update(hWnd);
}

int scene_manager::ChangeScene(HWND hWnd, WPARAM wp)
{
	if(wp < 0 || wp >= NumSceneName)
	{
		return -1;
	}
	int Ret = CurrentScene->Finalize(hWnd);
	if (Ret != 0)
	{
		return Ret;
	}
	CurrentScene = Scenes[wp];
	return CurrentScene->Initialize(hWnd);
}