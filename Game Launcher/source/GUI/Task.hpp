#pragma once

#include <Windows.h>

#ifndef INCLUDE_TASK_HPP
#define INCLUDE_TASK_HPP


class Task
{
protected:
	HWND hWnd;

public:
	Task(HWND hWnd)
		: hWnd(hWnd)
	{

	}
	//シーンが切り替わった時の初期処理
	virtual int initialize()
	{
		return 0;
	}
	//シーンが切り替わった時の終了処理
	virtual int finalize()
	{
		return 0;
	}
	//ビットマップの反映
	virtual int paint()
	{
		return 0;
	}
	//マウスカーソルがクライアントエリア上で動いたとき
	virtual int mouseMove(unsigned short x, unsigned short y, unsigned int param)
	{
		return 0;
	}
	//マウス左ボタンがクリックされた（下がった）とき
	virtual int buttonLDown(unsigned short x, unsigned short y)
	{
		return 0;
	}
	//マウス左ボタンがクリックされた（上がった）とき
	virtual int buttonLUp(unsigned short x, unsigned short y)
	{
		return 0;
	}
	//マウス右ボタンがクリックされた（下がった）とき
	virtual int buttonRDown(unsigned short x, unsigned short y)
	{
		return 0;
	}
	//マウス右ボタンがクリックされた（上がった）とき
	virtual int buttonRUp(unsigned short x, unsigned short y)
	{
		return 0;
	}
	//シーンの更新処理
	virtual int update()
	{
		return 0;
	}
};


#endif