#include "framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HPEN Brick_Gray_Pen, Brick_Red_Pen, Brick_Blue_Pen ;
HBRUSH Brick_Gray_Brush, Brick_Red_Brush, Brick_Blue_Brush;
DWORD startTime = 0; // timer 

DWORD endTime = GetTickCount(); // Получить текущее время
DWORD elapsedTime = endTime - startTime;

int playerX = 704; // начальная позиция квадратика по оси X
int playerY = 544; // начальная позиция квадратика по оси Y

enum Ebrick_type
{
    none,
    gray,
    red,
    blue
};

short Level1[20][30] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1},
        {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}; 

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOW));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//---------------------------------------------------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(0,0,0));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
//---------------------------------------------------------------------------------------------------
// Настройка при старте
void Init()
{
    Brick_Gray_Pen = CreatePen(PS_SOLID, 0, RGB(127, 127, 127));
    Brick_Gray_Brush = CreateSolidBrush(RGB(127, 127, 127)); 

    Brick_Red_Pen = CreatePen(PS_SOLID, 0, RGB(237, 28, 36));
    Brick_Red_Brush = CreateSolidBrush(RGB(237, 28, 36));

    Brick_Blue_Pen = CreatePen(PS_SOLID, 0, RGB(0, 162, 232));
    Brick_Blue_Brush = CreateSolidBrush(RGB(0, 162, 232));
}
//
//---------------------------------------------------------------------------------------------------
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   Init(); // Инициализация 

   RECT window_rect;
   window_rect.left = 0;
   window_rect.top = 0;
   window_rect.right = 960;
   window_rect.bottom = 604;

   AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, TRUE);

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, 0,
      0, 0, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top , nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//---------------------------------------------------------------------------------------------------
//Рисует стены
void Draw_Wall(HDC hdc, int x , int y, int x2, int y2, Ebrick_type brick_type)
{   
    HPEN pen;
    HBRUSH brush;

    switch (brick_type)
    {
        case none:
            return;
        case gray: 
            pen = Brick_Gray_Pen;
            brush = Brick_Gray_Brush; 
            break;
        case red: 
            pen = Brick_Red_Pen;
            brush = Brick_Red_Brush;
            break;
        case blue:
            pen = Brick_Blue_Pen;
            brush = Brick_Blue_Brush;
            break;
        default: 
            return;
    }
    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    Rectangle(hdc, x, y, x2 , y2);
}

//---------------------------------------------------------------------------------------------------
// Цикл рисует лабиринт из массива short Level1
void DrawMaze(HDC hdc, int cellSize) 
{
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 30; j++) {
            if (Level1[i][j] == 1) {
                int x = j * cellSize;
                int y = i * cellSize;
                int x2 = x + cellSize;
                int y2 = y + cellSize;
                Draw_Wall(hdc, x, y, x2, y2, gray);
            }
        }
    }
}

//---------------------------------------------------------------------------------------------------
// Рисует экран игры
void Draw_Frame(HDC hdc)
{
    if (playerX < 0) playerX = 0;
    if (playerX > 30 * 32) playerX = 30 * 32 - 32;
    if (playerY < 0) playerY = 0;
    if (playerY > 20 * 32) playerY = 20 * 32 - 32;
    //draw maze
    DrawMaze(hdc, 32);
    //exit
    Draw_Wall(hdc, 768, 0, 800, 32, blue);
    //player
    Draw_Wall(hdc, playerX, playerY, playerX + 32, playerY + 32, red);
}
//---------------------------------------------------------------------------------------------------
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

//---------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     // начальная позиция квадратика по оси Y
switch (message)
    {
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
            if (Level1[playerY / 32][(playerX - 32) / 32] != 1)
                playerX -= 32;
            break;
        case VK_RIGHT:
            if (Level1[playerY / 32][(playerX + 32) / 32] != 1)
                playerX += 32;
            break;
        case VK_UP:
            if (Level1[(playerY - 32) / 32][playerX / 32] != 1)
                playerY -= 32;
            break;
        case VK_DOWN:
            if (Level1[(playerY + 32) / 32][playerX / 32] != 1)
                playerY += 32;
            break;
        }

        if (wParam == VK_SPACE)  // Пример: начать движение при нажатии клавиши "пробел"
            startTime = GetTickCount(); // Запомнить время начала прохождения

        // Проверяем, достиг ли игрок красной черты
        if (playerX >= 768 && playerY == 0)
        {
            wchar_t buffer[100];
            DWORD endTime = GetTickCount();
            DWORD elapsedTime = (endTime - startTime) / 1000;
            swprintf(buffer, 100, L"Вы победили \nВремя прохождения: %d сек.", elapsedTime);
            MessageBox(hWnd, buffer,  L"Вы победили!", MB_OK | MB_ICONINFORMATION);
            // Добавьте здесь код для перезапуска игры или выхода из неё
        }
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;


    
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
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
            // TODO: Add any drawing code that uses hdc here...
            Draw_Frame(hdc);
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

//---------------------------------------------------------------------------------------------------
// Message handler for about box.
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
//---------------------------------------------------------------------------------------------------
