#include "ApplicationTime.h"

long long ApplicationTime::time = 0;
float ApplicationTime::deltaTime = 0.000001f;
long long ApplicationTime::checkTime = 0;
int ApplicationTime::fps = 0;
int ApplicationTime::fpsCounter = 0;
long long ApplicationTime::nowTime = 0;


void ApplicationTime::Initialize()
{
	time = GetNowHiPerformanceCount();
	deltaTime = 0.000001f;
	checkTime = GetNowHiPerformanceCount();
	fps = 0;
	fpsCounter = 0;
}

void ApplicationTime::Update()
{
	nowTime = GetNowHiPerformanceCount();
	deltaTime = (float)(nowTime - time);

	time = nowTime;
	fpsCounter++;
	if (nowTime - checkTime > 1000000) {
		fps = fpsCounter;
		fpsCounter = 0;
		checkTime = nowTime;
	}
}