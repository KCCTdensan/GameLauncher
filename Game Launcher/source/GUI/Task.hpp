#pragma once

#include <Windows.h>

#ifndef INCLUDE_TASK_HPP
#define INCLUDE_TASK_HPP


class Task
{
public:
	//シーンが切り替わった時の初期処理
	virtual int Initialize(HWND hWnd)
	{
		return 0;
	}
	//シーンが切り替わった時の終了処理
	virtual int Finalize(HWND hWnd)
	{
		return 0;
	}
	//ビットマップの反映
	virtual int Paint(HWND hWnd)
	{
		return 0;
	}
	//マウスカーソルがクライアントエリア上で動いたとき
	virtual int MouseMove(HWND hWnd, WPARAM wp, LPARAM lp)
	{
		return 0;
	}
	//マウス左ボタンがクリックされた（下がった）とき
	virtual int LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
	{
		return 0;
	}
	//マウス左ボタンがクリックされた（上がった）とき
	virtual int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
	{
		return 0;
	}
	//マウス右ボタンがクリックされた（下がった）とき
	virtual int RButtonDown(HWND hWnd, WPARAM wp, LPARAM lp)
	{
		return 0;
	}
	//マウス右ボタンがクリックされた（上がった）とき
	virtual int RButtonUp(HWND hWnd, WPARAM wp, LPARAM lp)
	{
		return 0;
	}
	//シーンの更新処理
	virtual int Update(HWND hWnd)
	{
		return 0;
	}
};


#endif