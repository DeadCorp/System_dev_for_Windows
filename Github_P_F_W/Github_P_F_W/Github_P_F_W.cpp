//#include "stdafx.h" // убрал, т.к. не использую прекомпилированный заголовок
//#include "Win32Project10.h" // аналогично
#include <tchar.h> // для макроса _T
#include <windows.h>
#define _USE_MATH_DEFINES
#include <cmath>
#define CIRCLE_CX 150.0
#define CIRCLE_CY 150.0
#define CIRCLE_BIG_RADIUS 100.0
#define CIRCLE_SMALL_RADIUS 40.0
#define ANGLE_COUNT 5
#define ID_BUTTON1 100
#define ID_BUTTON2 200
#define ID_BUTTON3 300
#define ID_CHILD1 1500
#define ID_CHILD2 1501

// значения, определяющие, что мы будем на окошке рисовать
// отмечу, что они нумеруются с 1, потому что GetWindowLong() возвращает 0, если пользовательских данных не было задано
#define DRAW_TRIANGLE 1
#define DRAW_ELLIPSE 2
#define DRAW_STAR 3


// --- Описание функции главного окна
LRESULT CALLBACK main_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//(СALLBACK - паскалевское соглашение о способе передаче параметров)
LRESULT CALLBACK child_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//(СALLBACK - паскалевское соглашение о способе передаче параметров)

HINSTANCE  hInst;
// --- Глобальные переменные


TCHAR main_ClassName[] = L"MainWindows";      // Название класса окна
TCHAR child_ClassName[] = L"ChildWindows";
TCHAR szTitle[] = L"ORIGINAL NAME ";

TCHAR main_app_name[] = L"LAB 7";      // Название класса окна
TCHAR popup_app_name[] = L"POPUPWINDOW";
TCHAR child_app_name[] = L"CHILDWINDOW";

// --- Функция WinMain
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	WNDCLASS main_wc, popup_wc, child_wc, child_wc1;

	HWND main_hWnd;
	MSG msg;
	memset(&main_wc, 0, sizeof(main_wc));
	memset(&popup_wc, 0, sizeof(popup_wc));
	memset(&child_wc, 0, sizeof(child_wc));


	main_wc.lpszClassName = main_ClassName;
	main_wc.lpfnWndProc = (WNDPROC)main_WndProc;
	main_wc.style = CS_HREDRAW | CS_VREDRAW;//стили класса окна Перерисовывает все окно , если регулятор движения или размер изменения высоты клиентской области.
	main_wc.hInstance = hInstance;
	main_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	main_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	main_wc.hbrBackground = CreateSolidBrush(RGB(20, 150, 1000));
	main_wc.lpszMenuName = NULL;
	main_wc.cbClsExtra = 0;
	main_wc.cbWndExtra = 0;
	RegisterClass(&main_wc);

	child_wc.lpszClassName = child_ClassName;
	child_wc.lpfnWndProc = (WNDPROC)child_WndProc;
	child_wc.style = CS_HREDRAW | CS_VREDRAW;
	child_wc.hInstance = hInstance;
	child_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	child_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	child_wc.hbrBackground = CreateSolidBrush(RGB(0, 255, 0));
	child_wc.lpszMenuName = NULL;
	child_wc.cbClsExtra = 0;
	child_wc.cbWndExtra = 0;
	RegisterClass(&child_wc);


	main_hWnd = CreateWindow(
		main_ClassName,             // Имя класса окон
		main_app_name,          // Заголовок окна
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,        // Стиль окна  
		CW_USEDEFAULT,          // X-координаты
		CW_USEDEFAULT,          // Y-координаты
		CW_USEDEFAULT,          // Ширина окна
		CW_USEDEFAULT,          // Высота окна
		NULL,           // Дескриптор окна-родителя
		NULL,           // Дескриптор меню окна
		hInstance,      // Дескриптор экземпляра приложения
		NULL);      // Дополнительная информация
	if (main_hWnd == 0)
	{
		return FALSE;
	}
	ShowWindow(main_hWnd, nCmdShow);
	UpdateWindow(main_hWnd);


	while (GetMessage(&msg, NULL, 0, 0)) //(NULL - дикриптор окна из которого принимать сообщения)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam; // возвращает значение последнего обработанного сообщения
}

// --- Функция окна
LRESULT CALLBACK main_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HWND hButton, hButton1, hButton2;
	switch (msg)
	{
	case WM_CREATE:
		hButton = CreateWindow(L"button", L"Відкрити нове вікно", WS_CHILD | WS_VISIBLE  | BS_PUSHBUTTON, 12, 12, 180, 40, hWnd, (HMENU)ID_BUTTON1, hInst, NULL);
		//hButton1 = CreateWindow(L"button", NULL, WS_CHILD | WS_VISIBLE | BS_BITMAP, 400, 162, 200, 150, hWnd, (HMENU)ID_BUTTON2, hInst, NULL);
		//hButton2 = CreateWindow(L"button", NULL, WS_CHILD | WS_VISIBLE | BS_BITMAP, 400, 312, 200, 150, hWnd, (HMENU)ID_BUTTON3, hInst, NULL);

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (LOWORD(wParam) == ID_BUTTON1)
		{
			HWND child_hWnd1 = CreateWindow(child_ClassName,szTitle, WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 20, 30, 300, 300, hWnd, (HMENU)ID_CHILD1, hInst, NULL);
			// как-то так.
			//SetWindowLong(child_hWnd1, GWL_USERDATA, DRAW_TRIANGLE);
			ShowWindow(child_hWnd1, SW_NORMAL);
			UpdateWindow(child_hWnd1);
			
			// не совсем так.
			//SetWindowLongPtr(child_hWnd1, GWLP_USERDATA, (LONG)child_WndProc);
			break;
		}
		if (LOWORD(wParam) == ID_BUTTON2)
		{
			// лишняя единичка?
			//HWND child_hWnd2 = CreateWindow(child_ClassName1, _T("Child2"), WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 700, 200, 400, 400, hWnd, (HMENU)ID_CHILD2, hInst, NULL);
			HWND child_hWnd2 = CreateWindow(child_ClassName, _T("Child2"), WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 700, 200, 400, 400, hWnd, (HMENU)ID_CHILD2, hInst, NULL);
			// этот параметр нужно задать каждому окошку при создании
			//SetWindowLong(child_hWnd2, GWL_USERDATA, DRAW_ELLIPSE);
			ShowWindow(child_hWnd2, SW_NORMAL);
			UpdateWindow(child_hWnd2);
			break;
		}
		if (LOWORD(wParam) == ID_BUTTON3)
		{
			HWND child_hWnd3 = CreateWindow(child_ClassName, _T("Child3"), WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 400, 300, 400, 400, hWnd, NULL, hInst, NULL);
			// ...каждому.
			//SetWindowLong(child_hWnd3, GWL_USERDATA, DRAW_STAR);
			ShowWindow(child_hWnd3, SW_NORMAL);
			UpdateWindow(child_hWnd3);
			break;
		}
		// чо это было?..
		//switch (wParam)
		//{


		//}


	case WM_PAINT:
	{

		// PAINTSTRUCT ps;
		// EndPaint(hWnd, &ps);
	}; break;


	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}; break;


	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0l;
}

LRESULT CALLBACK child_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{


	PAINTSTRUCT ps;
	HDC hdc;
	switch (msg)
	{

	case WM_PAINT:

	{
		// в оконную процедуру уже передается декскриптор того окна, для которого эта процедура вызвана, хранить их где-то ещё нет смысла
		// и точки с запятой не хватало
								 //LONG whatToDraw=GetWindowLongPtr(child_hWnd1, GWLP_USERDATA)
		



		hdc = BeginPaint(hWnd, &ps);

		

		EndPaint(hWnd, &ps);
		break;


	}
	}

	switch (msg)
	{


		// я не хочу, чтобы вся программа завершалась при закрытии дочернего окна
				//case WM_DESTROY:
				//{
				//                                 PostQuitMessage(0);
				//}; break;

	case WM_MOVE:
	{
		InvalidateRect(hWnd, NULL, TRUE); UpdateWindow(hWnd);
	}break;

	default: return DefWindowProc(hWnd, msg, wParam, lParam); //реализует поведение по умолчанию типичного окна верхнего уровня.
	}
	return 0l;
}