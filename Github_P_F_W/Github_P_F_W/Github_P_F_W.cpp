// Github_P_F_W.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Github_P_F_W.h"




#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
const TCHAR szTitle[MAX_LOADSTRING] = _T("Lab_1");                  // Текст строки заголовка
const TCHAR szWindowClass[MAX_LOADSTRING] = _T("Migal Mykola");            // имя класса главного окна
const TCHAR text[MAX_LOADSTRING] = _T("TUT SHOTO NAPISANO");


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	
	// TODO: Разместите код здесь.

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
	wcex.hCursor = LoadCursor(nullptr, IDC_HELP);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 6);
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
		0,
		0,
		1800,
		1000,
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
	static HBITMAP hBmp;
	static BITMAP  bmp;
	HDC hdc;              // индекс контекста устройства
	PAINTSTRUCT ps;       // структура для рисования
	static TEXTMETRIC tm; // структура для записи метрик
						  // шрифта
	
	switch (message)
	{
	case WM_CREATE :
	{
		hdc = GetDC(hWnd);

		// контекст отображения
		GetTextMetrics(hdc, &tm);
		
		
		ReleaseDC(hWnd, hdc);
		return 0;
	}
	break;
	case WM_RBUTTONDBLCLK:
	{
		DestroyWindow(hWnd);
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
		//int i = tm.tmHeight;          //напевно середнє значення величини символу рядка
		//int j = tm.tmInternalLeading; //напевно величина простору над символом для спеціальних знаків
		//int x = SM_CXDOUBLECLK;       //Ширина прямокутника дабл клик
		//int y = SM_CYDOUBLECLK;       //Висота прямокутника дабл клик
		//int v = ASPECTX;              //відносна ширина точки

		//wchar_t xstr[100]; //Ширина прямокутника дабл клик
		//wchar_t ystr[100]; //Висота прямокутника дабл клик
		//wchar_t istr[100]; //напевно середнє значення величини символу рядка
		//wchar_t jstr[100]; //напевно величина простору над символом для спеціальних знаків
		//wchar_t vstr[100]; //відносна ширина точки

		//
		//
		//_itow_s(x, xstr, 10);
		//_itow_s(y, ystr, 10);
		//_itow_s(i, istr, 10);
		//_itow_s(j, jstr, 10);
		//_itow_s(v, vstr, 10);
		 
		
		//hBmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));

		
		PAINTSTRUCT ps;
		RECT rt;
		HDC hdc = BeginPaint(hWnd, &ps);
		
		
		
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		GetClientRect(hWnd, &rt);		
		
		





		/*TextOut(hdc, 19, 0, L"Ширина прямокутника дабл клик", 30);
		TextOut(hdc, 19, 18, L"Висота прямокутника дабл клик" , 30);
		TextOut(hdc, 19, 36, L"напевно середнє значення величини символу рядка" , 48);
		TextOut(hdc, 19, 54, L"напевно величина простору над символом для спеціальних знаків" , 62);
		TextOut(hdc, 19, 72, L"відносна ширина точки", 22);
		

		TextOut(hdc, 0, 0 , xstr, sizeof(*xstr));
		TextOut(hdc, 0, 18, ystr, sizeof(*ystr));
		TextOut(hdc, 0, 36, istr, sizeof(*istr));
		TextOut(hdc, 0, 54, jstr, sizeof(*jstr));
		TextOut(hdc, 0, 72, vstr, sizeof(*vstr));*/



		
		
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
