#pragma once
#include <windows.h>
#include <tchar.h>

class ExePath 
{
public:
	static const TCHAR* GetPath()
	{
		static ExePath path;
		return path.m_Path;
	}

private:
	ExePath();

protected:
	TCHAR m_Path[MAX_PATH];
};

ExePath::ExePath()
{

	if (::GetModuleFileName(NULL, m_Path, MAX_PATH))    //���s�t�@�C���̃t���p�X���擾
	{   //�擾�ɐ���
		TCHAR* ptmp = _tcsrchr(m_Path, _T('\\')); // \�̍Ō�̏o���ʒu���擾
		if (ptmp != NULL)
		{   //�t�@�C�������폜
			ptmp = _tcsinc(ptmp);   //�ꕶ���i�߂�
			*ptmp = _T('\0');
		}
		else
		{
			//�G���[�F\������
		}
	}
	else
	{
		//�G���[�F�擾�Ɏ��s
	}
}