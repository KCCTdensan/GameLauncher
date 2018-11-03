#pragma once

#include <Windows.h>
#include <contents.hpp>

#ifndef INCLUDE_EDIT_HPP
#define INCLUDE_EDIT_HPP


namespace edit
{
	bool Prepare(HWND hWnd);
	void Command(HWND hWnd, WPARAM msg, WPARAM ID);
	void Paint(HWND hWnd);
	contents GetContents();
	void SetContents(const contents&Contents);
	void UpdateCommentNumOfWritten(HWND hWnd);
}


#endif