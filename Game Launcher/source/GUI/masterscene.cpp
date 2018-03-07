#include "masterscene.hpp"
#include "startup.hpp"
#include "mainmenu.hpp"


MasterScene::MasterScene(HWND hWnd, SceneName FirstScene, unsigned short BmpWidth, unsigned short BmpHeight) :Scene(BmpWidth, BmpHeight)
{
	Scenes[Scene_StartUp] = new StartUp(hWnd, BmpWidth, BmpHeight);
	Scenes[Scene_MainMenu] = new MainMenu(hWnd, BmpWidth, BmpHeight);

	CurrentScene = Scenes[FirstScene];
	CurrentScene->Initialize(hWnd);
}

MasterScene::~MasterScene()
{
	for (int i = 0; i < NumSceneName; i++)
	{
		delete Scenes[i];
	}
}

int MasterScene::Initialize(HWND hWnd)
{
	CurrentScene->Initialize(hWnd);
	return 0;
}

int MasterScene::Finalize(HWND hWnd)
{
	CurrentScene->Finalize(hWnd);
	return 0;
}

int MasterScene::Paint(HWND hWnd)
{
	return CurrentScene->Paint(hWnd);
}

int MasterScene::ChangeScene(HWND hWnd, int NextScene)
{
	if (NextScene < 0 || NextScene >= NumSceneName)
	{
		return -1;
	}
	if (CurrentScene->Finalize(hWnd) < 0)
	{
		return -2;
	}
	CurrentScene = Scenes[NextScene];
	if (CurrentScene->Initialize(hWnd) < 0)
	{
		return -3;
	}
	return 0;
}