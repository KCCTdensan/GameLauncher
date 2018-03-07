#pragma once

#include <Windows.h>
#include "MemDC.hpp"

#ifndef INCLUDE_SCENE_HPP
#define INCLUDE_SCENE_HPP


class Scene :public MemDC
{
public:
	Scene(unsigned short BmpWidth, unsigned short BmpHeight);
	virtual int Initialize(HWND hWnd) = 0;//�V�[�����؂�ւ�������̏�������
	virtual int Finalize(HWND hWnd) = 0;//�V�[�����؂�ւ�������̏I������
	virtual int Paint(HWND hWnd);//��{�I�ɕ`�悵���r�b�g�}�b�v�̔��f�̂�
	virtual int MouseMove(HWND hWnd, WPARAM wp, LPARAM lp);//�}�E�X�J�[�\�����N���C�A���g�G���A��œ������Ƃ�
	virtual int LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp);//�}�E�X���{�^�����N���b�N���ꂽ�i���������j�Ƃ�
	virtual int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);//�}�E�X���{�^�����N���b�N���ꂽ�i�オ�����j�Ƃ�
	virtual int RButtonDown(HWND hWnd, WPARAM wp, LPARAM lp);//�}�E�X�E�{�^�����N���b�N���ꂽ�i���������j�Ƃ�
	virtual int RButtonUp(HWND hWnd, WPARAM wp, LPARAM lp);//�}�E�X�E�{�^�����N���b�N���ꂽ�i�オ�����j�Ƃ�
	virtual int Update(HWND hWnd);//�V�[���̍X�V����
};


#endif