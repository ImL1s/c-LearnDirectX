#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/* Abbreviated description:
 * p    = untyped pointer
 * lp   = generic long pointer
 * lpsz = long pointer to a null-terminated string(with \0 end)
 * w    = Word(2 byte short integer)
 * dw   = DWord(4 byte integer)
 * IDI  = ID for Icon
 * IDC  = ID for Control
 */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstabce, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	// 1. define a window
	char *lpszClassName = TEXT("MyWindow");
	char *lpszTitle = TEXT("hello world");

	//wndclass.style = 0;			// defult style
	wndclass.style = CS_DBLCLKS;	// can receive double click event style
	wndclass.lpfnWndProc = WndProc;	// assign process fuction
	wndclass.cbClsExtra = 0;		// window class has no extra
	wndclass.cbWndExtra = 0;		// window instance has no extra
	wndclass.lpszMenuName = NULL;	// no menu for window
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = lpszClassName;							// assign class name
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// use default icon								
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);					// use arrow cursor
	wndclass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH)); // white backgroud

	// 2. register window
	if (!RegisterClass(&wndclass))
	{
		MessageBeep(0);
		return FALSE;
	}

	// 3. create window
	hwnd = CreateWindow(
		lpszClassName,			// class name
		lpszTitle,				// title name
		WS_OVERLAPPEDWINDOW,	// window style
		CW_USEDEFAULT,			// default x
		CW_USEDEFAULT,			// default y
		CW_USEDEFAULT,			// default width
		CW_USEDEFAULT,			// default height
		NULL,					// no parent window
		NULL,					// no menu
		hInstance,				// associate handler and window
		NULL);					// no parameter

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// return message to system when end of message loop
	return msg.wParam;
}

// on event call back
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	switch (message)
	{
		// left mouse button double click
	case WM_LBUTTONDBLCLK:
		PostQuitMessage(0);		// close window
		return 0;

		// right button click down
	case WM_RBUTTONDOWN:
		MessageBox(hwnd, TEXT("Hello"), TEXT("Hello"), 0);
		return 0;

		// try not to intercept left mouse button messages, there will be a lot of problems   
	//case WM_NCLBUTTONDOWN:
	//	//MessageBox(hwnd, TEXT("Hello"), TEXT("Hello"), 0);
	//	//PostQuitMessage(0);
	//	return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Ellipse(hdc, 0, 0, 1920, 100);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("Hello world!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}
}