#include<Windows.h>
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
		//MessageBox(NULL, "����� ���� �� ���������������(��� �� ����� �� ��� =( )", "Error", MB_OK | MB_ICONERROR);
		
		return 0;
	}

	//2)�������� ����:
	
	HWND hwnd = CreateWindowEx
		(
			NULL, 
			g_sz_WINDOW_ClASS,		//��� ������ ����
			g_sz_WINDOW_ClASS,		//��������� ����
			WS_OVERLAPPEDWINDOW,	//������� ���� ���������, ��� ���������� TopLevelWindow

			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,

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
		break;
	case WM_COMMAND:


	case WM_DESTROY:DestroyWindow(0);
		break;

	case WM_CLOSE: DestroyWindow(hwnd);
		break;

	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}