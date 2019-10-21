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

	if (::GetModuleFileName(NULL, m_Path, MAX_PATH))    //実行ファイルのフルパスを取得
	{   //取得に成功
		TCHAR* ptmp = _tcsrchr(m_Path, _T('\\')); // \の最後の出現位置を取得
		if (ptmp != NULL)
		{   //ファイル名を削除
			ptmp = _tcsinc(ptmp);   //一文字進める
			*ptmp = _T('\0');
		}
		else
		{
			//エラー：\が無い
		}
	}
	else
	{
		//エラー：取得に失敗
	}
}