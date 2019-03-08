#pragma once

#include <Windows.h>

#ifndef INCLUDE_TASK_HPP
#define INCLUDE_TASK_HPP


class Task
{
public:
	virtual int Initialize(HWND hWnd) = 0;							//�V�[�����؂�ւ�������̏�������
	virtual int Finalize(HWND hWnd) = 0;							//�V�[�����؂�ւ�������̏I������
	virtual int Paint(HWND hWnd) = 0;								//��{�I�ɕ`�悵���r�b�g�}�b�v�̔��f�̂�
	virtual int MouseMove(HWND hWnd, WPARAM wp, LPARAM lp) = 0;		//�}�E�X�J�[�\�����N���C�A���g�G���A��œ������Ƃ�
	virtual int LButtonDown(HWND hWnd, WPARAM wp, LPARAM lp) = 0;	//�}�E�X���{�^�����N���b�N���ꂽ�i���������j�Ƃ�
	virtual int LButtonUp(HWND hWnd, WPARAM wp, LPARAM lp) = 0;		//�}�E�X���{�^�����N���b�N���ꂽ�i�オ�����j�Ƃ�
	virtual int RButtonDown(HWND hWnd, WPARAM wp, LPARAM lp) = 0;	//�}�E�X�E�{�^�����N���b�N���ꂽ�i���������j�Ƃ�
	virtual int RButtonUp(HWND hWnd, WPARAM wp, LPARAM lp) = 0;		//�}�E�X�E�{�^�����N���b�N���ꂽ�i�オ�����j�Ƃ�
	virtual int Update(HWND hWnd) = 0;								//�V�[���̍X�V����
};


#endif