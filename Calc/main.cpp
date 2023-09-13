#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<Windows.h>
#include"resource.h"



CONST CHAR* g_sz_VALUES[] = { "One style", "Two style", "Norm Style" };

CONST CHAR g_sz_WINDOW_ClASS[] = "My Calculator";
CONST CHAR g_sz_DEFAULT_SKIN[] = "square_blue";

//g_ Global
//sz_ String Zero
CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;
CONST INT g_i_BTN_START_X = g_i_START_X;
CONST INT g_i_INTREVAL_BUTTON = 10;
CONST INT g_i_BTN_SIZE = 48;
CONST INT g_i_BTN_SIZE_WITH_INTERVAL = g_i_BTN_SIZE + g_i_INTREVAL_BUTTON;

CONST INT g_i_DISPLAY_HEIGHT = 50;
CONST INT g_i_DISPLAY_WIDTH = g_i_BTN_SIZE * 5 + g_i_INTREVAL_BUTTON * 4;

CONST INT g_i_BTN_START_Y = g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTREVAL_BUTTON;


CONST INT g_i_BTN_SIZE_DOUBLE = g_i_BTN_SIZE * 2 + g_i_INTREVAL_BUTTON;

CONST INT g_i_HEIGHT = g_i_BTN_SIZE + g_i_INTREVAL_BUTTON;

CONST CHAR g_OPERATIONS[] = "+-*/";

CONST CHAR g_sz_DISPLAY_FONT[] = "Tahoma";
CONST INT g_i_DISPLAY_FONT_HEIGHT = g_i_DISPLAY_HEIGHT - 2;
CONST INT g_i_DISPLAY_FONT_WIDTH = g_i_DISPLAY_FONT_HEIGHT / 2.5;



LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID SetSkin(HWND hwnd, CONST CHAR sz_skin[]);

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
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        (g_i_BTN_SIZE_WITH_INTERVAL * 5 + g_i_START_X * 2.5), (g_i_BTN_SIZE_WITH_INTERVAL * 5 + g_i_START_Y * 5) + 100,
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

    static DOUBLE a = 0;
    static DOUBLE b = 0;
    static INT operation = 0;
    static BOOL input = FALSE;
    static BOOL operation_input = false;

    switch (uMsg)
    {
    case WM_CREATE:
    {

#define BTN_STYLE WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON 

        HWND hDisplay = CreateWindowEx
        (
            0, "Static", "0",
            WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_SUNKEN | SS_CENTERIMAGE,
            g_i_START_X, g_i_START_Y,
            g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
            hwnd,
            (HMENU)IDC_STATIC,
            GetModuleHandle(NULL),
            NULL
        );
       /* LOGFONT lFont;
        ZeroMemory(&lFont, sizeof(lFont));
        lFont.lfHeight = 32;
        lFont.lfWeight = 20;
        lFont.lfEscapement = 0;
        lFont.lfOrientation = 0;
        lFont.lfWeight = 500;
        lFont.lfItalic = FALSE;
        lFont.lfUnderline = FALSE;
        lFont.lfStrikeOut = FALSE;
        lFont.lfCharSet = DEFAULT_CHARSET;
        lFont.lfOutPrecision = OUT_TT_PRECIS;
        lFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
        lFont.lfQuality = ANTIALIASED_QUALITY;
        lFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
        strcpy(lFont.lfFaceName, "Arial");

        HFONT hFont = CreateFontIndirect(&lFont);*/

        HFONT hFont = CreateFont
        (
            g_i_DISPLAY_FONT_HEIGHT, g_i_DISPLAY_FONT_WIDTH,
            GM_ADVANCED, 0, FW_DEMIBOLD,
            FALSE, FALSE, FALSE,
            DEFAULT_CHARSET,
            OUT_CHARACTER_PRECIS,
            CLIP_CHARACTER_PRECIS,
            ANTIALIASED_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            g_sz_DISPLAY_FONT
        );
        SendMessage(hDisplay, WM_SETFONT, (WPARAM)hFont, TRUE);
                    
        // неоптимизорованые кнопки
        /*CreateWindowEx
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
        );*/
        ////////////////////////////////////////////////////////////////////////////////
                /*INT i_digit = 1;
                CHAR sz_digit[2] = {};
                for (int i = 3; i >= 1; i--)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        sz_digit[0] = i_digit + (char)48;
                        CreateWindowEx
                        (
                            0, "Button", sz_digit,
                            BTN_STYLE,
                            g_i_START_X + (g_i_BTN_SIZE_WITH_INTERVAL) * j,
                            g_i_START_Y + (g_i_BTN_SIZE_WITH_INTERVAL) * i,
                            g_i_BTN_SIZE, g_i_BTN_SIZE,
                            hwnd,
                            (HMENU)(IDC_BUTTON_0 + i_digit),
                            GetModuleHandle(NULL),
                            NULL

                        );
                        i_digit++;
                    }
                }*/
        INT i_digit = 1;
        CHAR sz_digit[2] = {};
        for (int i = 2; i >= 0; i--)
        {
            for (int j = 0; j < 3; j++)
            {
                sz_digit[0] = i_digit + (char)48;
                CreateWindowEx
                (
                    0, "Button", sz_digit,
                    BTN_STYLE | BS_BITMAP,
                    g_i_BTN_START_X + g_i_BTN_SIZE_WITH_INTERVAL * j,
                    g_i_BTN_START_Y + g_i_BTN_SIZE_WITH_INTERVAL * i,
                    g_i_BTN_SIZE, g_i_BTN_SIZE,
                    hwnd,
                    (HMENU)(IDC_BUTTON_0 + i_digit),
                    GetModuleHandle(NULL),
                    NULL

                );
                i_digit++;
            }
        }

        //////////////////////////////////////////////////////
        CreateWindowEx
        (
            0, "Button", " 0 ",
            BTN_STYLE | BS_BITMAP,
            g_i_START_X, g_i_BTN_START_Y + g_i_BTN_SIZE_WITH_INTERVAL * 3,
            g_i_BTN_SIZE_DOUBLE, g_i_BTN_SIZE,
            hwnd,
            (HMENU)IDC_BUTTON_0,
            GetModuleHandle(NULL),
            NULL
        );
        SetSkin(hwnd, g_sz_DEFAULT_SKIN);
        CreateWindowEx
        (
            0, "Button", " . ",
            BTN_STYLE,
            g_i_START_X + g_i_BTN_SIZE_WITH_INTERVAL * 2, g_i_BTN_START_Y + g_i_BTN_SIZE_WITH_INTERVAL * 3,
            g_i_BTN_SIZE, g_i_BTN_SIZE,
            hwnd,
            (HMENU)IDC_BUTTON_POINT,
            GetModuleHandle(NULL),
            NULL
        );
        ////////////////////////////////////////////////////
        INT i_operation = 0;
        CHAR sz_operation[2] = {};


        for (int i = 3; i >= 0; i--)
        {
            sz_operation[0] = g_OPERATIONS[i];
            CreateWindowEx
            (
                0, "Button", sz_operation,
                BTN_STYLE,
                g_i_BTN_START_X + g_i_BTN_SIZE_WITH_INTERVAL * 3, g_i_BTN_START_Y + g_i_BTN_SIZE_WITH_INTERVAL * (3 - i),
                g_i_BTN_SIZE, g_i_BTN_SIZE,
                hwnd,
                (HMENU)(IDC_BUTTON_PLUS + i),
                GetModuleHandle(NULL),
                NULL
            );
        }
        //HWND hBtnPlus = GetDlgItem(hwnd, IDC_BUTTON_PLUS);
        //HBITMAP hBitMap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_PLUS));
        //SendMessage(hBtnPlus, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitMap);


        CreateWindowEx
        (
            0, "Button", "<---",
            BTN_STYLE,
            g_i_BTN_START_X + g_i_BTN_SIZE_WITH_INTERVAL * 4, g_i_BTN_START_Y,
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
            g_i_BTN_START_X + g_i_BTN_SIZE_WITH_INTERVAL * 4, g_i_BTN_START_Y + g_i_BTN_SIZE_WITH_INTERVAL,
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
            g_i_BTN_START_X + g_i_BTN_SIZE_WITH_INTERVAL * 4, g_i_BTN_START_Y + g_i_BTN_SIZE_WITH_INTERVAL * 2,
            g_i_BTN_SIZE, g_i_BTN_SIZE_DOUBLE,
            hwnd,
            (HMENU)IDC_BUTTON_EQUAL,
            GetModuleHandle(NULL),
            NULL
        );


    }
    break;

    case WM_CTLCOLOREDIT:
    {
        HDC hdc = (HDC)wParam;
        SetBkMode(hdc, OPAQUE);
        SetBkColor(hdc, RGB(0, 0, 100)); HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
        SetTextColor(hdc, RGB(255, 0, 0));
        return (LRESULT)hBrush;
    }
    break;

    case WM_COMMAND:
    {
        CONST INT SIZE = 256;
        CHAR sz_buffer[SIZE] = {};
        HWND hStatic = GetDlgItem(hwnd, IDC_STATIC); //взяли Статик

        SendMessage(hStatic, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);


        if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9 || LOWORD(wParam) == IDC_BUTTON_POINT)
        {
            DOUBLE d_buffer = atof(sz_buffer);
            if (d_buffer == a)
            {
                SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)"");
                sz_buffer[0] = 0;
            }

            CHAR sz_symbol[2] = {};
            sz_symbol[0] = CHAR(LOWORD(wParam) - IDC_BUTTON_0 + '0');
            if (LOWORD(wParam) == IDC_BUTTON_POINT)
            {
                if (strchr(sz_buffer, '.'))break;
                sz_symbol[0] = '.';
            }
            strcat(sz_buffer, sz_symbol);
            //if (sz_buffer[0] == '0' && strchr(sz_buffer, '.') == 0)memmove(&sz_buffer[0], &sz_buffer[1], strlen(sz_buffer)-1);
            SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
            input = TRUE;

        }
        if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
        {
            SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)"");
            a = b = operation = 0;
            input = FALSE;
            operation_input = FALSE;
        }
        if (LOWORD(wParam) == IDC_BUTTON_CLEAR_LAST_NUMBER)
        {
            if (strcmp(sz_buffer, "0") == 0 || strlen(sz_buffer) == 0) break;
            sz_buffer[strlen(sz_buffer) - 1] = 0;
            SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
        }

        if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
        {
            SendMessage(hStatic, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
            if (input)
            {
                b = atof(sz_buffer);
                input = FALSE;
            }
            if (a == 0)a = b;
            SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0);
            operation = LOWORD(wParam);
            /*switch (LOWORD(wParam))
            {
            case IDC_BUTTON_PLUS:	operation = '+';		break;
            case IDC_BUTTON_MINUS:	operation = '-';		break;
            case IDC_BUTTON_ASTER:	operation = '*';		break;
            case IDC_BUTTON_SLASH:	operation = '/';		break;
            }*/
            operation_input = TRUE;
        }
        if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
        {
            if (input)
            {
                SendMessage(hStatic, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
                b = atof(sz_buffer);
                input = FALSE;
            }
            /*switch (operation)
            {
            case '+':	a += b;		break;
            case '-':	a -= b;		break;
            case '*':	a *= b;		break;
            case '/':	a /= b;		break;
            }*/
            switch (operation)
            {
            case IDC_BUTTON_PLUS:	a += b;		break;
            case IDC_BUTTON_MINUS:	a -= b;		break;
            case IDC_BUTTON_ASTER:	a *= b;		break;
            case IDC_BUTTON_SLASH:	a /= b;		break;
            }
            operation_input = FALSE;
            sprintf(sz_buffer, "%F", a);
            SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
        }




    }
    case WM_KEYDOWN:
    {
        if (GetKeyState(VK_SHIFT) < 0)
        {
            if (wParam == 0x38)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
        }
        else if (wParam >= 0x30 && wParam <= 0x39)
        {
            SendMessage(hwnd, WM_COMMAND, wParam - 0x30 + 1000, 0);
        }
        else if (LOWORD(wParam) >= 0x60 && LOWORD(wParam) <= 69)
            SendMessage(hwnd, WM_COMMAND, wParam - 0x60 + 1000, 0);
        switch (LOWORD(wParam))
        {
        case VK_OEM_PERIOD: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_POINT, 0); break;
        case VK_OEM_PLUS: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_PLUS, 0); break;
        case VK_OEM_MINUS: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_MINUS, 0); break;
        case VK_MULTIPLY: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0); break;
        case VK_DIVIDE: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SLASH, 0); break;
        case VK_BACK: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_CLEAR_LAST_NUMBER, 0); break;
        case VK_RETURN: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0); break;
        case VK_ESCAPE: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_CLEAR, 0); break;
        }
    }
    break;
    case WM_CONTEXTMENU:
    {
        HMENU hMenu = CreatePopupMenu();
        InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, IDC_EXIT, "Exit");
        InsertMenu(hMenu, 0, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
        InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, IDC_SQUARE, "Square buttons");
        InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, IDC_ROUND, "Round buttons");

        switch (TrackPopupMenuEx(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN | TPM_RETURNCMD, LOWORD(lParam), HIWORD(lParam), hwnd, NULL))
        {
        case IDC_ROUND:SetSkin(hwnd, "round_blue"); break;
        case IDC_SQUARE: SetSkin(hwnd, "square_blue"); break;
        case IDC_EXIT: SendMessage(hwnd, IDC_EXIT, 0, 0);
        }
    }
    break;
    case WM_DESTROY:PostQuitMessage(0); break;
    case IDC_EXIT:
    case WM_CLOSE: DestroyWindow(hwnd); break;
    default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return NULL;
}
VOID SetSkin(HWND hwnd, CONST CHAR sz_skin[])
{

    CONST int SIZE = 10;
    HWND hButton[SIZE] = {};
    for (int i = 0; i < SIZE; i++)
    {
        hButton[i] = GetDlgItem(hwnd, i + IDC_BUTTON_0);
        //GetDlgItem(hwnd, i + 1000);
        CHAR sz_filename[FILENAME_MAX] = {};
        sprintf(sz_filename, "buttonsbmp\\%s\\button_%i.bmp",sz_skin, i);
        HBITMAP hBitmap = (HBITMAP)LoadImage(
            GetModuleHandle(NULL),
            sz_filename,
            IMAGE_BITMAP,
            i > 0 ?  g_i_BTN_SIZE :  g_i_BTN_SIZE_DOUBLE, g_i_BTN_SIZE,
            LR_LOADFROMFILE
        );
        // hBitMap[i] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(i + 100));
        SendMessage(hButton[i], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
      /*  DWORD dwErrorID = GetLastError();
        LPSTR lpMessageBuffer = NULL;
        DWORD dwSize = FormatMessage
        (
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dwErrorID,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_RUSSIAN_RUSSIA),
            (LPSTR)&lpMessageBuffer,
            0,
            NULL
        );*/
        //MessageBox(hwnd, lpMessageBuffer, "Erro", MB_OK | MB_ICONERROR);
    }
}