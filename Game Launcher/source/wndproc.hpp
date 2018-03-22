#pragma once

#include <Windows.h>

#ifndef INCLUDE_WNDPROC
#define INCLUDE_WNDPROC


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


#endif