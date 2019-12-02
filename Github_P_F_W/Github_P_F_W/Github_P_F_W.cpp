// Github_P_F_W.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Github_P_F_W.h"
#include "resource.h"
#include "Windows.h"
#include "iostream"
#include "commctrl.h"
#include "stdlib.h"
#include "commdlg.h"
#include <string>
using namespace std;


#define x_co 0
#define IDB_Button1 1
#define MAX_LOADSTRING 1000000

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
const TCHAR szTitle[MAX_LOADSTRING] = _T("Lab_6");                  // Текст строки заголовка
const TCHAR szWindowClass[MAX_LOADSTRING] = _T("Mudri slowa");            // имя класса главного окна
const TCHAR text[MAX_LOADSTRING] = _T("text text text");
HCURSOR CUR1,CUR2,CUR0;
int chislo;


wchar_t chislo_s[MAX_LOADSTRING];
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    cur(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	

	// Инициализация глобальных строк

	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GITHUBPFW));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;// CS_NOCLOSE
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(hInst,IDC_HELP);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + x_co);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GITHUBPFW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
	

	HWND hWnd = CreateWindowW(szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		nullptr);

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

LRESULT CALLBACK  WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	static int cxClient, cyClient;
	
	static HBITMAP hBmp;
	static BITMAP  bmp;
	static HBRUSH bkbrush = NULL;
	static HWND hBtn, hBtn2;// дескриптор кнопки
	HANDLE hf;
	HFILE ht;
	RECT rc;
	HDC hdc;              // индекс контекста устройства
	PAINTSTRUCT ps;       // структура для рисования
	static TEXTMETRIC tm; // структура для записи метрик
						  // шрифта
	static POINT pt;//для захвата курсора


	

	switch (message)
	{
	case WM_KEYDOWN:
	{
		
		return 0;
	}
	case WM_CREATE :
	{
		hdc = GetDC(hWnd);
		
		
		
		hBmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
		GetObject(hBmp, sizeof(BITMAP), &bmp);
		// контекст отображения
		GetTextMetrics(hdc, &tm);
		
		
		ReleaseDC(hWnd, hdc);
		return 0;
	}
	
	
	case WM_LBUTTONDOWN :
	{
		
		
		chislo += 1;
		InvalidateRect(hWnd, NULL, TRUE);
		
		

	}
	
	
	case WM_COMMAND:
	{
		
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
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
		RECT rt;
		HGDIOBJ hOld;
		HDC hMemDC,hdc = BeginPaint(hWnd, &ps);
		// Получаем текущие экранные
		// координаты курсора мыши 
		GetCursorPos(&pt);

		// Преобразуем экранные координаты
		// в оконные координаты
		ScreenToClient(hWnd, &pt);
		//ClientToScreen(hWnd, &pt);

			
		
		_itow_s(chislo, chislo_s, 10);
	TextOut(hdc, pt.x, pt.y, chislo_s , wcslen(chislo_s));
		



		
		
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		DeleteObject(hBmp);
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

	
	
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		
		
	
		
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break; }
	
	}
	return (INT_PTR)FALSE;

	
}


