#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR g_sz_WINDOW_ClASS[] = "My Window Class";


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	//1)����������� ������ ����:
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;


	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_TORI));	//������ ������������ � ������ �����
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_ELUMINATE));	//������ ������������ � ������ ���������
	wc.hIcon = (HICON)LoadImage(hInstance, "start_icon.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "start_icon_mini.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));		//��������� ���� ��� ��������� �� ����
	wc.hCursor = (HCURSOR)LoadImage(hInstance, "star_curs.cur", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		//���� ���� ����


	wc.hInstance = hInstance;					//�������� ��������� ���������
	wc.lpfnWndProc = WndProc;					//��������� �� ��������� ����
	wc.lpszMenuName = NULL;						//��� �������� ���� ��� ��� ����, 
	//��� �������� ���� - ��� ID  ������� ����� ��������
	wc.lpszClassName = g_sz_WINDOW_ClASS;		//��� ������ ����. ��������� ����� ���� ����������� ������-�� ������,
	//�.�. ��������� ����� ���� ������-�� ����(������, ��������� ����)
	//������ ��� ��������� ����� ���� �������������� ������ Button

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "����� ���� �� ���������������(��� �� ����� �� ��� =( )", "Error", MB_OK | MB_ICONERROR);

		return 0;
	}

	//2)�������� ����:

	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int window_width = ScreenWidth * 0.75;
	int window_height = ScreenHeight * 0.75;
	int start_x = ScreenWidth * 0.125;
	int start_y = ScreenHeight * 0.125;

	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOW_ClASS,		//��� ������ ����
		g_sz_WINDOW_ClASS,		//��������� ����
		WS_OVERLAPPEDWINDOW,	//������� ���� ���������, ��� ���������� TopLevelWindow

		start_x, start_y,
		window_width, window_height,

		NULL,					//Parent (��� ���� �������� ������������ �����)
		NULL,					//��� �������� ���� ��� ��� ����, 
								//��� �������� ���� - ��� ID  ������� ����� ��������
		hInstance,				//���� ��� ������� ������� � hInstance, �������� ������ ��� �� �� �������� ��� ��� ��������,
								//�� ��� ������ ����� �������� ��� ������ ������� GetModulHandle(NULL)
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "���� �� �����������, �� ����� ������� ���� �� ��������", "�������� ����������", MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);		//������ ����� ����������� ����
	UpdateWindow(hwnd);				//��������� ���������� ����



	//3)������ ����� ���������:
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{

		CHAR sz_static_text[] = "���� Static control ������ ��� ������ ������� CreateWindowEx()";
		CreateWindowEx
		(
			0, "Static", sz_static_text,
			WS_CHILD | WS_VISIBLE,
			100, 100,
			strlen(sz_static_text) * 7.2, 20,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Button", "OK",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			strlen(sz_static_text) * 7.1, 140,
			100, 20,
			hwnd,
			(HMENU)IDC_BUTTON,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			0, "Edit", "",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 120,
			strlen(sz_static_text) * 7.2, 20,
			hwnd,
			(HMENU)IDC_EDIT_TEXT,
			GetModuleHandle(NULL),
			NULL
		);
	}
	break;
	case WM_SIZE:
		
	case WM_MOVE: 
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		sprintf(sz_buffer, "%s, Position: %ix%i | Size: %ix%i", g_sz_WINDOW_ClASS, rect.left, rect.top, width, height);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON: 
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_TEXT), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(GetDlgItem(hwnd, IDC_STATIC), WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		};

		break;

	case WM_DESTROY:PostQuitMessage(0);
		break;

	case WM_CLOSE: DestroyWindow(hwnd);
		break;

	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}