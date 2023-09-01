#include<Windows.h>
#include"resource.h"



CONST CHAR g_sz_WINDOW_ClASS[] = "My Calculator";
//g_ Global
//sz_ String Zero
CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 15;
CONST INT g_i_INTREVAL_BUTTON = 10;
CONST INT g_i_BTN_SIZE = 50;
CONST INT g_i_BTN_SIZE_DOUBLE = g_i_BTN_SIZE * 2 + g_i_INTREVAL_BUTTON;
CONST INT g_i_HEIGHT = g_i_BTN_SIZE + g_i_INTREVAL_BUTTON;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;

	wc.hIcon = (HICON)LoadImage(hInstance, "icon_calc.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "icon_calc_mini.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_WINDOW_ClASS;

	//проверка регистрации класса окна
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Класс окна не зарегистрирован(Что то пошло не так =( )", "Error", MB_OK | MB_ICONERROR);

		return 0;
	}
	
	//2) Создание окна
	
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOW_ClASS,
		g_sz_WINDOW_ClASS,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		(g_i_BTN_SIZE * 5 + g_i_INTREVAL_BUTTON * 5 + g_i_START_X * 2.5), (g_i_BTN_SIZE * 5 + g_i_INTREVAL_BUTTON * 8 + g_i_START_Y * 2),
		NULL,
		NULL,
		hInstance,
		NULL
	);

		if (hwnd == NULL)
		{
			MessageBox(NULL, "Ошибка создание окна", "Полезная информация", MB_OK | MB_ICONINFORMATION);
			return 0;
		}
	ShowWindow(hwnd, nCmdShow);		
	UpdateWindow(hwnd);

	//3) Запуск цикла сообщений

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{

#define BTN_STYLE WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON 

		HWND hDisplay = CreateWindowEx
		(
			0, "Static", "Static ",
			WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_SUNKEN | SS_CENTERIMAGE ,
			g_i_START_X, g_i_START_Y,
			g_i_BTN_SIZE * 5 + g_i_INTREVAL_BUTTON * 4, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " 0 ",
			BTN_STYLE,
			g_i_START_X, g_i_HEIGHT * 4 + g_i_START_Y,
			g_i_BTN_SIZE_DOUBLE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " 1 ",
			BTN_STYLE,
			g_i_START_X, g_i_HEIGHT * 3 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_1,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " 2 ",
			BTN_STYLE,
			g_i_START_X + g_i_BTN_SIZE + g_i_INTREVAL_BUTTON, g_i_HEIGHT * 3 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_2,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " 3 ",
			BTN_STYLE,
			g_i_START_X + g_i_BTN_SIZE * 2 + g_i_INTREVAL_BUTTON * 2, g_i_HEIGHT * 3 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_3,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " 4 ",
			BTN_STYLE,
			g_i_START_X, g_i_HEIGHT * 2 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_4,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " 5 ",
			BTN_STYLE,
			g_i_START_X + g_i_BTN_SIZE + g_i_INTREVAL_BUTTON, g_i_HEIGHT * 2 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_5,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " 6 ",
			BTN_STYLE,
			g_i_START_X + g_i_BTN_SIZE * 2 + g_i_INTREVAL_BUTTON * 2, g_i_HEIGHT * 2 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_6,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " 7 ",
			BTN_STYLE,
			g_i_START_X, g_i_HEIGHT + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_7,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " 8 ",
			BTN_STYLE,
			g_i_START_X + g_i_BTN_SIZE + g_i_INTREVAL_BUTTON, g_i_HEIGHT + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_8,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " 9 ",
			BTN_STYLE,
			g_i_START_X + g_i_BTN_SIZE*2 + g_i_INTREVAL_BUTTON*2, g_i_HEIGHT + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_9,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " . ",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + g_i_BTN_SIZE_DOUBLE + g_i_INTREVAL_BUTTON, g_i_HEIGHT * 4 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " / ",
			BTN_STYLE,
			g_i_START_X + (g_i_BTN_SIZE + g_i_INTREVAL_BUTTON)*3, g_i_HEIGHT + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_SLASH,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " * ",
			BTN_STYLE,
			g_i_START_X + (g_i_BTN_SIZE + g_i_INTREVAL_BUTTON) * 3, g_i_HEIGHT * 2 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_ASTER,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " --- ",
			BTN_STYLE,
			g_i_START_X + (g_i_BTN_SIZE + g_i_INTREVAL_BUTTON) * 3, g_i_HEIGHT * 3 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_MINUS,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " + ",
			BTN_STYLE,
			g_i_START_X + (g_i_BTN_SIZE + g_i_INTREVAL_BUTTON) * 3, g_i_HEIGHT * 4 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_PLUS,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", "<---",
			BTN_STYLE,
			g_i_START_X*2 + g_i_BTN_SIZE * 4 + g_i_INTREVAL_BUTTON * 3, g_i_HEIGHT + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLEAR_LAST_NUMBER,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " C ",
			BTN_STYLE,
			g_i_START_X * 2 + g_i_BTN_SIZE * 4 + g_i_INTREVAL_BUTTON * 3, g_i_HEIGHT * 2 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", " = ",
			BTN_STYLE,
			g_i_START_X *2 + g_i_BTN_SIZE * 4 + g_i_INTREVAL_BUTTON * 3, g_i_HEIGHT * 3 + g_i_START_Y,
			g_i_BTN_SIZE, g_i_BTN_SIZE_DOUBLE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);

	}
		break;
	case WM_COMMAND:
	{


		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_0:
		{

		}
		break;
		};
	}
		break;
	case WM_DESTROY:PostQuitMessage(0); break;
	case WM_CLOSE: DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}