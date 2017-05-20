#include "d3dUtility.h"

// D3DFVF_XYZRHW = has x,y,z,rhw
// D3DFVF_DIFFUSE = has color
#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

IDirect3DDevice9* Device = 0;
// video memory pointer
LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;

struct stD3DVertex
{
	float x, y, z, rhw;
	unsigned long color;
};

bool Setup()
{
	// pre init something
	unsigned long col = D3DCOLOR_XRGB(255, 255, 255);

	// in main memory
	stD3DVertex objDate[] = 
	{
		{ 420.0f,150.0f,0.5f,1.0f,col },
		{ 420.0f,350.0f,0.5f,1.0f,col },
		{ 220.0f,150.0f,0.5f,1.0f,col },
		{ 220.0f,350.0f,0.5f,1.0f,col }
	};

	// to video memory
	Device->CreateVertexBuffer(sizeof(objDate), 0, D3DFVF_VERTEX, &g_VertexBuffer,NULL);

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