#pragma once

#include <Windows.h>
#include <contents.hpp>


namespace edit
{
	bool Prepare(HWND hWnd);
	void Command(HWND hWnd, WPARAM msg, WPARAM ID);
	void Paint(HWND hWnd);
	Contents GetContents();
	void SetContents(const Contents &contents);
	void UpdateCommentNumOfWritten(HWND hWnd);
}