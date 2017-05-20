#include "d3dUtility.h"

// D3DFVF_XYZRHW = has x,y,z,rhw
// D3DFVF_DIFFUSE = has color
#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

// represents display card
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
	unsigned long col = D3DCOLOR_XRGB(0, 255, 255);

	// in main memory
	stD3DVertex objData[] =
	{
		{ 420.0f,150.0f,0.5f,1.0f,col },
		{ 420.0f,350.0f,0.5f,1.0f,col },
		{ 220.0f,150.0f,0.5f,1.0f,col },
		{ 220.0f,350.0f,0.5f,1.0f,col }
	};

	// Create vertex buffer(在顯存中開闢頂點緩存空間)
	if (FAILED(Device->CreateVertexBuffer(sizeof(objData), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &g_VertexBuffer, NULL)))
	{
		return FALSE;
	}

	void* ptr;

	// Lock vertex buffer(每次操作顯存中的資料時需要Lock一下)
	if (FAILED(g_VertexBuffer->Lock(0, sizeof(g_VertexBuffer), (void**)&ptr, 0)))
		return FALSE;

	// copy data to video memory
	memcpy(ptr, objData, sizeof(objData));

	// unlock
	g_VertexBuffer->Unlock();

		return true;
}

bool Display(float timeDelta)
{
	if (Device)
	{
		// 這些操作都是在後台緩衝中進行的
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x000000, 1.0f, 0);
		Device->BeginScene();

		// 將頂點緩存與數據流綁定(將幾何體的信息傳輸到繪製流水線中)
		Device->SetStreamSource(0, g_VertexBuffer, 0, sizeof(stD3DVertex));
		// 設定靈活頂點格式
		Device->SetFVF(D3DFVF_VERTEX);
		// 設定畫圖模式為線條
		Device->DrawPrimitive(D3DPT_LINELIST, 0, 2);

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
	// width must be 645+,否則線條渲染不出來
	d3d::InitD3D(hinstance, 645, 480, true, D3DDEVTYPE_HAL, &Device);
	Setup();

	// 消息循環
	d3d::EnterMsgLoop(Display);

	Cleanup();
	Device->Release();
}