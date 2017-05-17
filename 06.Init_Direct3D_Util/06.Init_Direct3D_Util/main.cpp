#include "d3dUtility.h"

IDirect3DDevice9* Device = 0;

bool Setup()
{
	// pre init something
	return true;
}

bool Display(float timeDelta)
{
	if (Device)
	{
		// make background black
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x000000, 1.0f, 0);
		Device->BeginScene();

		// render something

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

void Cleanup()
{
	// release something
}


LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		// if key is ESC,quit window
		if (wParam == VK_ESCAPE)
			DestroyWindow(hwnd);
		break;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	d3d::InitD3D(hinstance, 640, 480, true, D3DDEVTYPE_HAL, &Device);
	Setup();

	// ®ø®§´`Àô
	d3d::EnterMsgLoop(Display);

	Cleanup();
	Device->Release();
}