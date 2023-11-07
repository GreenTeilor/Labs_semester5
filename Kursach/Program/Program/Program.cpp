#include "framework.h"
#include "Program.h"
#include <map>
#include <string>
#include "Const.h"
#include "Field.h"

#define MAX_LOADSTRING 100

Field field{ 10, 10, 20 };
std::vector<HWND> buttons;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
HWND hWnd;                                      // Дескриптор окна
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Difficulty(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK fieldActions(HWND hButton, UINT message, WPARAM wParam, LPARAM lParam, 
    UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
void checkItem(HWND hWnd, int wmId);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.
    Const::loadImages(); //Images load

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROGRAM, szWindowClass, MAX_LOADSTRING);
    
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //Field creation
    int buttonNumber = 0;
    buttons.resize(10 * 10);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            HWND btnHwnd = CreateWindow(L"button", L"",
                WS_CHILD | WS_VISIBLE | BS_BITMAP | BS_NOTIFY | BS_PUSHBUTTON,
                1 + Const::imgWidth * j, 35 + Const::imgHeight * i, Const::imgWidth, Const::imgHeight, hWnd, (HMENU)buttonNumber, hInstance, 0);
            HBITMAP img = Const::images.at(Type::Types::CLOSED);
            SendMessage(btnHwnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)img);

            if (!SetWindowSubclass(GetDlgItem(hWnd, buttonNumber), fieldActions, 0, buttonNumber))
            {
                DestroyWindow(hWnd);
            }

            buttons[buttonNumber] = btnHwnd;

            buttonNumber++;
        }
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROGRAM));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROGRAM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROGRAM);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int buttonNumber = 0;
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_NEW:
                /*====================================*/

                //HERE CODE ON NEW GAME CREATION!!!
                field.generate(field.getWidth(), field.getHeight(), field.getNumMines());
                for (int i = 0; i < field.getHeight(); ++i)
                {
                    for (int j = 0; j < field.getWidth(); ++j)
                    {
                        SendMessage(buttons[i * field.getWidth() + j], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(field[i][j].getType()));
                    }
                }
                /*====================================*/
                break;
            case IDM_DIFFICULTY_EASY:
                //Code to set easy difficulty
                for (auto& btn : buttons)
                {
                    DestroyWindow(btn);
                }
                buttons.clear();
                field.generate(20, 20, 40);
                buttons.resize(field.getWidth() * field.getHeight());
                
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        HWND btnHwnd = CreateWindow(L"button", L"",
                            WS_CHILD | WS_VISIBLE | BS_BITMAP | BS_NOTIFY | BS_PUSHBUTTON,
                            1 + Const::imgWidth * j, 35 + Const::imgHeight * i, Const::imgWidth, Const::imgHeight, hWnd, (HMENU)buttonNumber, hInst, 0);
                        HBITMAP img = Const::images.at(Type::Types::CLOSED);
                        SendMessage(btnHwnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)img);

                        if (!SetWindowSubclass(GetDlgItem(hWnd, buttonNumber), fieldActions, 0, buttonNumber))
                        {
                            DestroyWindow(hWnd);
                        }

                        buttons[buttonNumber] = btnHwnd;

                        buttonNumber++;
                    }
                }

                checkItem(hWnd, IDM_DIFFICULTY_EASY);
                break;
            case IDM_DIFFICULTY_MEDIUM:
                //Code to set medium difficulty
                checkItem(hWnd, IDM_DIFFICULTY_MEDIUM);
                break;
            case IDM_DIFFICULTY_HARD:
                //Code to set hard difficulty
                checkItem(hWnd, IDM_DIFFICULTY_HARD);
                break;
            case IDM_DIFFICULTY_CUSTOM:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIFFICULTYBOX), hWnd, Difficulty);
                checkItem(hWnd, IDM_DIFFICULTY_CUSTOM);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break; 
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Обработчик сообщений для окна "Пользовательская сложность".
INT_PTR CALLBACK Difficulty(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            /*====================================*/

                //HERE CODE ON CHANGE DIFFICULTY PARAMS!!!

            /*====================================*/
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

LRESULT CALLBACK fieldActions(HWND btnHwnd, UINT message, WPARAM wParam, LPARAM lParam,
    UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    int x = dwRefData % field.getWidth(); //HAS TO BE DIVIDED BY ACTUAL FIELD WIDTH
    int y = dwRefData / field.getHeight(); //HAS TO BE DIVIDED BY ACTUAL FIELD WIDTH
    HBITMAP img = Const::images.at(Type::Types::EMPTY);
    
    switch (message)
    {
    case WM_LBUTTONDOWN:
        field.reveal(x, y);
        for (int i = 0; i < field.getHeight(); ++i)
        {
            for (int j = 0; j < field.getWidth(); ++j)
            {
                SendMessage(buttons[i*field.getWidth() + j], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(field[i][j].getType()));
            }
        }
        return TRUE;
    case WM_NCDESTROY:
        RemoveWindowSubclass(btnHwnd, fieldActions, uIdSubclass);
        return DefSubclassProc(btnHwnd, message, wParam, lParam);
    default:
        return DefSubclassProc(btnHwnd, message, wParam, lParam);
    }
    
}

void checkItem(HWND hWnd, int wmId) 
{
    CheckMenuItem(GetMenu(hWnd), IDM_DIFFICULTY_EASY, MF_BYCOMMAND | MF_UNCHECKED);
    CheckMenuItem(GetMenu(hWnd), IDM_DIFFICULTY_MEDIUM, MF_BYCOMMAND | MF_UNCHECKED);
    CheckMenuItem(GetMenu(hWnd), IDM_DIFFICULTY_HARD, MF_BYCOMMAND | MF_UNCHECKED);
    CheckMenuItem(GetMenu(hWnd), IDM_DIFFICULTY_CUSTOM, MF_BYCOMMAND | MF_UNCHECKED);

    CheckMenuItem(GetMenu(hWnd), wmId, MF_BYCOMMAND | MF_CHECKED);
}
