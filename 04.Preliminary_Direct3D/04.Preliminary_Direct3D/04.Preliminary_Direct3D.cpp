// 04.Preliminary_Direct3D.cpp : �w�q���ε{�����i�J�I�C
//

#include "stdafx.h"
#include "04.Preliminary_Direct3D.h"
#include <d3d9.h>

#define MAX_LOADSTRING 100

// �����ܼ�: 
HINSTANCE hInst;                                // �ثe�������
WCHAR szTitle[MAX_LOADSTRING];                  // ���D�C��r
WCHAR szWindowClass[MAX_LOADSTRING];            // �D�������O�W��

LPDIRECT3D9			g_pd3d;
LPDIRECT3DDEVICE9	g_p3dDevice;


// �o�ӵ{���X�Ҳդ��ҥ]�t���禡���V�e�ŧi: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


HRESULT InitD3D(HWND hwnd)
{
	// 01. create DIRECT3D9 object
	if (NULL == (g_pd3d = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// 02. set d3d setting
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	// 03. init d3d device
	// D3DCREATE_HARDWARE_VERTEXPROCESSING is fast,but compatibility is not good.
	// D3DCREATE_SOFTWARE_VERTEXPROCESSING is slow,but compatibility is good. 
	if (FAILED(g_pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_p3dDevice))) {
		return E_FAIL;
	}

	return S_OK;
}

// 04. Render
VOID Render() {
	if (NULL == g_p3dDevice) {
		return;
	}

	g_p3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	if (SUCCEEDED(g_p3dDevice->BeginScene())) {
		// DO SOME DRAWING
		g_p3dDevice->EndScene();
	}
	g_p3dDevice->Present(NULL, NULL, NULL, NULL);
}

// 05. Release
VOID Cleanup() {
	if (g_p3dDevice != NULL) {
		g_p3dDevice->Release();
	}

	if (g_pd3d != NULL) {
		g_pd3d->Release();
	}
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �b���m�J�{���X�C

    // ��l�ƥ���r��
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY04PRELIMINARY_DIRECT3D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // �������ε{����l�]�w: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY04PRELIMINARY_DIRECT3D));

    MSG msg;

    // �D�T���j��: 
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
//  �禡: MyRegisterClass()
//
//  �γ~: ���U�������O�C
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY04PRELIMINARY_DIRECT3D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY04PRELIMINARY_DIRECT3D);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �禡: InitInstance(HINSTANCE, int)
//
//   �γ~: �x�s������鱱��N�X�åB�إߥD����
//
//   ����: 
//
//        �b�o�Ө禡���A�ڭ̷|�N������鱱��N�X�x�s�b�����ܼƤ��A
//        �åB�إߩM��ܥD�{�������C
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �N������鱱��N�X�x�s�b�����ܼƤ�

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   if (FAILED(InitD3D(hWnd))) {
	   return false;
   }

   return TRUE;
}

//
//  �禡: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �γ~:     �B�z�D�������T���C
//
//  WM_COMMAND  - �B�z���ε{���\���
//  WM_PAINT    - ø�s�D����
//  WM_DESTROY  - ��ܵ����T���M���^
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // ��R�\���������: 
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
            //HDC hdc = BeginPaint(hWnd, &ps);
            //// TODO: �b���[�J����ϥ� hdc ��ø�ϵ{���X...
            //EndPaint(hWnd, &ps);
			Render();
			//ValidateRect(hWnd, NULL);
        }
        break;
    case WM_DESTROY:
		Cleanup();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// [����] ������T���B�z�`���C
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
