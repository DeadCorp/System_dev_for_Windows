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



#define x_co 0
#define IDB_Button1 1
#define MAX_LOADSTRING 1000000
#define ID_FIRSTCHILD	100
#define ID_SECONDCHILD	101
#define ID_THIRDCHILD	102
#define ID_FO 103
#define ID_FA 104
#define ID_SI 105
#define ID_SE 106
#define ID_AT 107



// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
const TCHAR szTitle[MAX_LOADSTRING] = _T("Lab_7");                  // Текст строки заголовка
const TCHAR szWindowClass[MAX_LOADSTRING] = _T("Migal Mykola");            // имя класса главного окна
const TCHAR text[MAX_LOADSTRING] = _T("TUT SHOTO NAPISANO");
HCURSOR CUR1,CUR2,CUR0;
PROCESS_INFORMATION processInfo;
//OPENFILENAME ofn;
//TCHAR szFile[260];
int i = 0;
int j = 0, j3 = 0, j4 = 0;
int xx = 0, yy = 0, cc = 0;


wchar_t s[MAX_LOADSTRING] = _T("");
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    cur(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK child_WndProc(HWND, UINT, WPARAM, LPARAM);


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
	WNDCLASSEXW child_wc;

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

	child_wc.lpszClassName = L"child";
	child_wc.lpfnWndProc = (WNDPROC)child_WndProc;
	child_wc.style = CS_HREDRAW | CS_VREDRAW;
	child_wc.hInstance = hInstance;
	child_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	child_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	child_wc.hbrBackground = CreateSolidBrush(RGB(0, 255, 0));
	child_wc.lpszMenuName = NULL;
	child_wc.cbClsExtra = 0;
	child_wc.cbWndExtra = 0;
	
	return RegisterClassExW(&wcex) and RegisterClassExW(&child_wc);
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
		1920,
		1080,
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
	static HWND hBtn, hBtn2, hBtn3; // дескриптор кнопки
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
		
		hBmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
		GetObject(hBmp, sizeof(BITMAP), &bmp);
		// контекст отображения
		
		
		
		
		return 0;
	}
	
	
	case WM_LBUTTONDOWN :
	{
		InvalidateRect(hWnd , NULL, TRUE);
	}
	case WM_SETCURSOR:
	{
		if (i == 1) {
			SetCursor(CUR1);
			break;
		}
		if (i == 2) {
			SetCursor(CUR2);
			break;
		}
		if (i == 0) {
			SetCursor(CUR0);
			
		}
		



	}
	
	case WM_COMMAND:
	{
		if (lParam == (LPARAM)hBtn3)
		{
			j = 1;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		if (lParam == (LPARAM)hBtn2)
		{
			j4 = 4;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		if (lParam == (LPARAM)hBtn)
		{
			j3 = 3;
			InvalidateRect(hWnd, NULL, TRUE);
		}

		
		
		
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_STEP:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, About);			
			break;
		case IDM_FAC:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hWnd, About);
			break;
		case IDM_AUTOR:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, About);
			break;
		}
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
		
		
		HBITMAP bmLogo1, bmLogo2;
		

		
		PAINTSTRUCT ps;
		RECT rt;
		HGDIOBJ hOld;
		HDC hdc = BeginPaint(hWnd, &ps);

		
			
			
		
		//Ellipse(hdc, 100, 100, 200, 200);
		
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		GetClientRect(hWnd, &rt);
		typedef UINT(*MUFUNC)(int x,int y);
		
		
		
			HMODULE hLib = LoadLibrary(L"DLL1.dll");
			if (hLib == NULL) {
				MessageBox(hWnd, L"errrrrrroooooorrrr", L"error", NULL);
				break;

			}

			MUFUNC step = (MUFUNC)GetProcAddress(hLib, "stepin");
			MUFUNC fac = (MUFUNC)GetProcAddress(hLib, "factorial");
		
			xx = IDC_EDIT1;
			yy = IDC_EDIT1;
			cc = IDC_EDIT3;
			j3 = step(6, 5);
			j4 = fac(5,0);
			lstrcat(s, _T("stepin 5 chisla 6 = "));
			TextOut(hdc, 19, 0, s, wcslen(s));
			_itow_s(j3, s, 10);			
			lstrcat(s, _T("   FACTORIAL   chisla 5 = "));
			TextOut(hdc, 160, 0, s, wcslen(s));
			_itow_s(j4, s, 10);
			TextOut(hdc, 360, 0, s, wcslen(s));
		/*TextOut(hdc, 19, 0, L"Ширина прямокутника дабл клик", 30);
		TextOut(hdc, 19, 18, L"Висота прямокутника дабл клик" , 30);
		TextOut(hdc, 19, 36, L"напевно середнє значення величини символу рядка" , 48);
		TextOut(hdc, 19, 54, L"напевно величина простору над символом для спеціальних знаків" , 62);
		TextOut(hdc, 19, 72, L"відносна ширина точки", 22);*/
		

		/*TextOut(hdc, 0, 0 , xstr, sizeof(*xstr));
		TextOut(hdc, 0, 18, ystr, sizeof(*ystr));
		TextOut(hdc, 0, 36, istr, sizeof(*istr));
		TextOut(hdc, 0, 54, jstr, sizeof(*jstr));
		TextOut(hdc, 0, 72, vstr, sizeof(*vstr));*/



		
		
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

		
		
		
		}// switch(whatToDraw)

		EndPaint(hWnd, &ps);
		break;


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
		switch (wmId)
		{
		case IDC_BUTTON1: {
			i = 0;
			break;

		}
		case IDC_BUTTON2: {
			i = 1;
			break;

		}
		case IDC_BUTTON3: {
			i = 2;
			break;

		}
		
			break;
		}
		
	
		
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			
			
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break; }
	
	}
	return (INT_PTR)FALSE;

	
}


