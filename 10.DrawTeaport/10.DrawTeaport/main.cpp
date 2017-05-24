#include "d3dUtility.h"

// D3DFVF_XYZRHW = has x,y,z,rhw
// D3DFVF_DIFFUSE = has color
//#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define WIDTH 1280
#define HEIGHT 720

// represents display card
IDirect3DDevice9* Device = 0;
ID3DXMesh *mesh = 0;


bool Setup()
{
	// pre init something
	unsigned long col = D3DCOLOR_XRGB(0, 255, 255);


	D3DXCreateTeapot(Device, &mesh, 0);


	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI*0.5f, (float)WIDTH / (float)HEIGHT, 1.0f, 1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

		return true;
}

bool Display(float timeDelta)
{
	if (Device)
	{
		D3DXMATRIX trans;
		D3DXMatrixTranslation(&trans, 0.0f, 0.0f, 3.0f);
		Device->SetTransform(D3DTS_WORLD, &trans);

		//// 這些操作都是在後台緩衝中進行的
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffff, 1.0f, 0);
		Device->BeginScene();
		mesh->DrawSubset(0);
		Device->EndScene();

		// Swap the back and front buffers
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
	// width must be 645+,否則線條渲染不出來 D3DDEVTYPE_HAL(on Windows)
	// 在mac虛擬機上必須使用REF軟件渲染
	d3d::InitD3D(hinstance, 1280, 720, true, D3DDEVTYPE_REF, &Device);
	Setup();

	// 消息循環
	d3d::EnterMsgLoop(Display);

	Cleanup();
	Device->Release();
}