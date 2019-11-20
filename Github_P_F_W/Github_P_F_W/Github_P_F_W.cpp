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
int j = 0;


int sec = 0;
wchar_t secx[MAX_LOADSTRING];
wchar_t secy[MAX_LOADSTRING];

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
		// Получаем текущие экранные
		// координаты курсора мыши 
		GetCursorPos(&pt);

		// Преобразуем экранные координаты
		// в оконные координаты
		ScreenToClient(hWnd, &pt);

		// Для клавиш позиционирования текстового
		// курсора изменяем соответствующим образом
		// координаты курсора мыши
		switch (wParam)
		{
		case VK_DOWN:  // вниз
		{
			pt.y += 20;
			break;
		}
		case VK_UP:    // вверх
		{
			pt.y -= 20;
			break;
		}
		case VK_LEFT:  // влево
		{
			pt.x -= 20;
			break;
		}
		case VK_RIGHT: // вправо
		{
			pt.x += 20;
			break;
		}
		case VK_RETURN :
		{
			
			SendMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
			//SendMessage(hWnd, WM_LBUTTONDOWN, wParam, lParam);
			 
			break;
		}
		case VK_SPACE:
		{
			i = 1;
			break;
		}
		case VK_SHIFT:
		{
			i = 2;
			break;
		}
		case VK_ESCAPE: {
			i = 0;
			break;
		}
		// Для всех остальных клавиш
		// ничего не делаем
		default:
		{
			return 0;
		}
		}

		// Получаем координаты внутренней
		// области окна
		GetClientRect(hWnd, &rc);

		// Вычисляем новые координаты курсора мыши
		// таким образом, чтобы курсор не выходил
		// за пределы окна
		pt.x = max(min(pt.x, rc.right), rc.left);
		pt.y = max(min(pt.y, rc.bottom), rc.top);

		// Преобразуем оконные координаты в экранные
		ClientToScreen(hWnd, &pt);

		// Устанавливаем курсор мыши
		// в новую позицию
		SetCursorPos(pt.x, pt.y);

		return 0;
	}
	case WM_CREATE :
	{
		/*hBtn = CreateWindow(_T("button"), _T( "Вибрати файл для запуску"),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 30, 325, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtn, SW_SHOWNORMAL);
		hBtn2 = CreateWindow(_T("button"), _T("Iнформація про запущені програмою процеси"),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 90, 325, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtn2, SW_SHOWNORMAL);*/
		hBtn3 = CreateWindow(_T("button"), _T("Відкрити нове вікно"),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 30, 325, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtn3, SW_SHOWNORMAL);
		hdc = GetDC(hWnd);
		
		
			CUR1 = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1)),
			CUR2 = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR2)),
			CUR0 = LoadCursor(hInst, IDC_HELP);
		
		hBmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
		GetObject(hBmp, sizeof(BITMAP), &bmp);
		// контекст отображения
		GetTextMetrics(hdc, &tm);
		
		
		ReleaseDC(hWnd, hdc);
		return 0;
	}
	
	
	case WM_LBUTTONDOWN :
	{
		/*if (wParam == MK_LBUTTON)
		{
			/*COLORREF bkcolor = RGB(rand() % 256, rand() % 256, rand() % 256);
			if (bkbrush)
				DeleteObject(bkbrush);
			bkbrush = CreateSolidBrush(bkcolor);
			SetClassLongPtr(hWnd, GCL_HBRBACKGROUND, (LONG)bkbrush);
			InvalidateRect(hWnd, NULL, TRUE);
	
			PAINTSTRUCT ps;
			RECT rc;
			HDC hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rc);
			SetDCBrushColor(hdc, bkcolor);
			FillRect(hdc, &rc, (HBRUSH)GetStockObject(DC_BRUSH));

			//or use ps.rcPaint to repaint only the section which requires update
			//FillRect(hdc, &ps.rcPaint, (HBRUSH)GetStockObject(DC_BRUSH));

			EndPaint(hWnd, &ps);
	*/
			

		//}
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
			HWND child_hWnd1 = CreateWindow(szWindowClass, L"Child1", WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0,100, 200, 200, hWnd, NULL, hInst, NULL);
			// как-то так.
			
			ShowWindow(child_hWnd1, SW_NORMAL);
			UpdateWindow(child_hWnd1);
			
			break;
			
			
		}
		/*if (lParam == (LPARAM)hBtn)    // если нажали на кнопку
		{
			OPENFILENAME ofn = { sizeof ofn };
			wchar_t file[1024];
			file[0] = '\0';
			ofn.lpstrFile = file;
			ofn.lpstrFileTitle = ofn.lpstrFile;
			ofn.nMaxFile = 1024;
			ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER;
			if (GetOpenFileName(&ofn) == TRUE)
			{
				
				
				
				STARTUPINFO si;
				PROCESS_INFORMATION pi;
				ZeroMemory(&si, sizeof(si));
				si.cb = sizeof(si);
				ZeroMemory(&pi, sizeof(pi));
				
				if (CreateProcess(NULL, ofn.lpstrFile,
					NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == TRUE)
				{
						lstrcat(secx, L"//////////////////////////////////////////////////////////////////////////");
						lstrcat(secx, L"\nІм'я файлу : ");
						lstrcat(secx, ofn.lpstrFileTitle);
						lstrcat(secx, L"\nАйді процесу : ");
						sec = pi.dwProcessId;
						_itow_s(sec, secy, 10);	
						lstrcat(secx, secy);
						sec = pi.dwThreadId;
						_itow_s(sec, secy, 10);
						lstrcat(secx, L"\nАйді потоку : ");
						lstrcat(secx, secy);
						lstrcat(secx, L"\n");
						CloseHandle(pi.hProcess);
						CloseHandle(pi.hThread);
				}
				

			}
		}
		if (lParam == (LPARAM)hBtn2)
		{
			

			MessageBox(hWnd, secx , L"Інформація про процес                                        ", MB_OK);

		}*/
		
		
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_CUR:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);			
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
		 
		
		HBITMAP bmLogo1, bmLogo2;
		

		
		PAINTSTRUCT ps;
		RECT rt;
		HGDIOBJ hOld;
		HDC hMemDC,hdc = BeginPaint(hWnd, &ps);
		
		
		
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		GetClientRect(hWnd, &rt);		
		
		hMemDC = CreateCompatibleDC(hdc);
		hOld = SelectObject(hMemDC, hBmp);

		/*StretchBlt(
			hdc,
			0, 0,
			cxClient, cyClient,
			hMemDC,
			0, 0,
			bmp.bmWidth, bmp.bmHeight,
			SRCCOPY);*/

		SelectObject(hMemDC, hOld);
		DeleteDC(hMemDC);
		
		
		
		

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


