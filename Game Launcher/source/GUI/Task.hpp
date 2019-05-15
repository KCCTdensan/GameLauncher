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
	//�V�[�����؂�ւ�������̏�������
	virtual int initialize()
	{
		return 0;
	}
	//�V�[�����؂�ւ�������̏I������
	virtual int finalize()
	{
		return 0;
	}
	//�r�b�g�}�b�v�̔��f
	virtual int paint()
	{
		return 0;
	}
	//�}�E�X�J�[�\�����N���C�A���g�G���A��œ������Ƃ�
	virtual int mouseMove(unsigned short x, unsigned short y, unsigned int param)
	{
		return 0;
	}
	//�}�E�X���{�^�����N���b�N���ꂽ�i���������j�Ƃ�
	virtual int buttonLDown(unsigned short x, unsigned short y)
	{
		return 0;
	}
	//�}�E�X���{�^�����N���b�N���ꂽ�i�オ�����j�Ƃ�
	virtual int buttonLUp(unsigned short x, unsigned short y)
	{
		return 0;
	}
	//�}�E�X�E�{�^�����N���b�N���ꂽ�i���������j�Ƃ�
	virtual int buttonRDown(unsigned short x, unsigned short y)
	{
		return 0;
	}
	//�}�E�X�E�{�^�����N���b�N���ꂽ�i�オ�����j�Ƃ�
	virtual int buttonRUp(unsigned short x, unsigned short y)
	{
		return 0;
	}
	//�V�[���̍X�V����
	virtual int update()
	{
		return 0;
	}
};


#endif