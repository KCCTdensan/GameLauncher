#pragma once

#include <Windows.h>
#include <contents.hpp>

#ifndef INCLUDE_EDIT_HPP
#define INCLUDE_EDIT_HPP


namespace EDIT
{
	bool Prepare(HWND hWnd);
	void Command(HWND hWnd, WPARAM msg, WPARAM ID);
	void Paint(HWND hWnd);
	CONTENTS GetContents();
	void SetContents(const CONTENTS&Contents);
	void UpdateCommentNumOfWritten(HWND hWnd);
}


#endif