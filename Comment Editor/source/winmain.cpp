#include <Windows.h>
#include "wnd.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	bool loop = true;
	MSG msg;

	if (WND::RegWndCls(hInstance) == 0)
	{
		return -1;
	}
#ifdef MDI
	if (WND::RegMDIChildCls(hInstance) == 0)
	{
		return -1;
	}
#endif
	if (!WND::CreateMainWnd())
	{
		return -1;
	}

	while (loop)
	{
		BOOL ret = GetMessage(&msg, NULL, 0, 0);

		switch (ret)
		{
		case -1:
		case 0:
			loop = false;
			break;

		default:
			DispatchMessage(&msg);
			TranslateMessage(&msg);
			break;
		}
	}

	return (int)msg.wParam;
}