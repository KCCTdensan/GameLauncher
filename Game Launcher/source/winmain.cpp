#include "window_procedure.hpp"


namespace
{
	constexpr LPTSTR windowClassName = TEXT("GAMELAUNCHER");

	ATOM registerWindowClass(HINSTANCE hInstance)
	{
		WNDCLASS wndcls;

		wndcls.style = CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = WndProc;
		wndcls.cbClsExtra = 0;
		wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInstance;
		wndcls.hIcon = NULL;
		wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = windowClassName;

		return RegisterClass(&wndcls);
	}

	bool createMainWindow()
	{
		RECT windowRect;

		GetWindowRect(GetDesktopWindow(), &windowRect);

		return CreateWindow(windowClassName, TEXT("Game Launcher"), WS_POPUP,
			0, 0, windowRect.right, windowRect.bottom,
			NULL, NULL, NULL, NULL) != NULL;
	}
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	bool loop = true;
	MSG msg;

	if (registerWindowClass(hInstance) == 0)
	{
		return -1;
	}

	if (!createMainWindow())
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
			break;
		}
	}

	return (int)msg.wParam;
}