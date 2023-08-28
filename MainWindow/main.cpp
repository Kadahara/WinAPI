#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_WINDOW_ClASS[] = "My Window Class";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	//1)Регистрация класса окна:
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;


	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_TORI));	//Иконка отображаемая в панеле задач
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_ELUMINATE));	//Иконка отображаемая в страке заголовка
	wc.hIcon = (HICON)LoadImage(hInstance, "start_icon.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "start_icon_mini.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));		//Указатель мыши при наведении на окно
	wc.hCursor = (HCURSOR)LoadImage(hInstance, "star_curs.cur", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		//Цвет фона окна


	wc.hInstance = hInstance;					//Экземляр запущеной программы
	wc.lpfnWndProc = WndProc;					//Указатель на процедуру окна
	wc.lpszMenuName = NULL;						//Для главного окна это Имя меню, 
												//для элемента окна - это ID  ресурса этого элемента
	wc.lpszClassName = g_sz_WINDOW_ClASS;		//Имя Класса окна. Абсолютно любое окно пренадлежит какому-то классу,
												//т.е. абсолютно любое окно какого-то типа(кнопка, текстовое поле)
												//кнопка это абсолютно любое окно принадлежащаяя классу Button

	if (!RegisterClassEx(&wc))
	{
		//MessageBox(NULL, "Класс окна не зарегистрирован(Что то пошло не так =( )", "Error", MB_OK | MB_ICONERROR);
		
		return 0;
	}

	//2)Создание окна:
	
	HWND hwnd = CreateWindowEx
		(
			NULL, 
			g_sz_WINDOW_ClASS,		//Имя класса окна
			g_sz_WINDOW_ClASS,		//Заголовок окна
			WS_OVERLAPPEDWINDOW,	//Главное окно программы, еще называется TopLevelWindow

			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,

			NULL,					//Parent (оно само является родительским окном)
			NULL,					//Для главного окна это Имя меню, 
									//для элемента окна - это ID  ресурса этого элемента
			hInstance,				//Если нет прямого доступа к hInstance, например потому что мы не получили его как параметр,
									//то его всегда можно получить при помощи функции GetModulHandle(NULL)
			NULL
		);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Окно не открывается, по этому откроем хотя бы форточку", "Полезная информация", MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);		//Задаем режим отображения окна
	UpdateWindow(hwnd);				//Выполняет прорисовку окна



	//3)Запуск цикла сообщений:
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