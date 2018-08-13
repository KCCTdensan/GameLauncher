#include "SceneManager.hpp"
#include "Scene/MainMenu.hpp"
#include "Scene/AppGallery.hpp"
#include "Scene/GameGallery.hpp"
#include "Scene/MusicGallery.hpp"
#include "Scene/PictureGallery.hpp"
#include "Scene/ModelGallery.hpp"
#include "Scene/VideoGallery.hpp"
#include "Scene/OthersGallery.hpp"


SceneManager::SceneManager(HWND hWnd, SceneName FirstScene, unsigned short BmpWidth, unsigned short BmpHeight)
{
	Scenes[SceneName_MainMenu] = new MainMenu(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_AppGallery] = new AppGallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_GameGallery] = new GameGallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_MusicGallery] = new MusicGallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_PictureGallery] = new PictureGallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_3DModelGallery] = new ModelGallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_VideoGallery] = new VideoGallery(hWnd, this, BmpWidth, BmpHeight);
	Scenes[SceneName_OthersGallery] = new OthersGallery(hWnd, this, BmpWidth, BmpHeight);
	CurrentScene = Scenes[FirstScene];
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < NumSceneName; i++)
	{
		delete Scenes[i];
		Scenes[i] = nullptr;
	}
	CurrentScene = nullptr;
}

int SceneManager::Initialize(HWND hWnd)
{
	return CurrentScene->Initialize(hWnd);
}

int SceneManager::Finalize(HWND hWnd)
{
	return CurrentScene->Finalize(hWnd);
}

int SceneManager::Paint(HWND hWnd)
{
	return CurrentScene->Paint(hWnd);
}

int SceneManager::MouseMove(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return CurrentScene->MouseMove(hWnd, wp, lp);
}

int SceneManager::LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return CurrentScene->LButtonDown(hWnd, wp, lp);
}

int SceneManager::LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return CurrentScene->LButtonUp(hWnd, wp, lp);
}

int SceneManager::RButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return CurrentScene->RButtonDown(hWnd, wp, lp);
}

int SceneManager::RButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
{
	return CurrentScene->RButtonUp(hWnd, wp, lp);
}

int SceneManager::Update(HWND hWnd)
{
	return CurrentScene->Update(hWnd);
}

int SceneManager::ChangeScene(HWND hWnd, SceneName NextScene)
{
	int Ret = CurrentScene->Finalize(hWnd);
	if (Ret != 0)
	{
		return Ret;
	}
	CurrentScene = Scenes[NextScene];
	return CurrentScene->Initialize(hWnd);
}