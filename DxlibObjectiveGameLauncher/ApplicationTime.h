#pragma once
#include "DxLib.h"
class ApplicationTime
{
public:
	static void Initialize();
	static void Update();
	static int GetFPS() { return fps; };
private:
	static long long nowTime;
	static long long time;
	static float deltaTime;
	static int fps;
	static int fpsCounter;
	static long long checkTime;
};

