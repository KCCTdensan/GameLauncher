#pragma once

#include <Windows.h>

#ifndef INCLUDE_TASK_HPP
#define INCLUDE_TASK_HPP


class Task
{
public:
	virtual int Initialize(HWND hWnd) = 0;							//シーンが切り替わった時の初期処理
	virtual int Finalize(HWND hWnd) = 0;							//シーンが切り替わった時の終了処理
	virtual int Paint(HWND hWnd) = 0;								//基本的に描画したビットマップの反映のみ
	virtual int MouseMove(HWND hWnd, WPARAM wp, LPARAM lp) = 0;		//マウスカーソルがクライアントエリア上で動いたとき
	virtual int LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp) = 0;	//マウス左ボタンがクリックされた（下がった）とき
	virtual int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp) = 0;		//マウス左ボタンがクリックされた（上がった）とき
	virtual int RButtonDown(HWND hWnd, WPARAM wp, LPARAM lp) = 0;	//マウス右ボタンがクリックされた（下がった）とき
	virtual int RButtonUp(HWND hWnd, WPARAM wp, LPARAM lp) = 0;		//マウス右ボタンがクリックされた（上がった）とき
	virtual int Update(HWND hWnd) = 0;								//シーンの更新処理
};


#endif