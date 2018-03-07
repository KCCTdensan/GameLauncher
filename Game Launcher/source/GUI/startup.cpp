#include "startup.hpp"


StartUp::StartUp(HWND hWnd, unsigned short BmpWidth, unsigned short BmpHeight) :Scene(BmpWidth, BmpHeight)
{

}

StartUp::~StartUp()
{

}

int StartUp::Initialize(HWND hWnd)
{
	return 0;
}

int StartUp::Finalize(HWND hWnd)
{
	return 0;
}

int StartUp::Paint(HWND hWnd)
{
	return 0;
}