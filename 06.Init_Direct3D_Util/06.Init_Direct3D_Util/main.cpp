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

	// Create vertex buffer(�b��s���}�P���I�w�s�Ŷ�)
	if (FAILED(Device->CreateVertexBuffer(sizeof(objData), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &g_VertexBuffer, NULL)))
	{
		return FALSE;
	}

	void* ptr;

	// Lock vertex buffer(�C���ާ@��s������ƮɻݭnLock�@�U)
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
		// �o�Ǿާ@���O�b��x�w�Ĥ��i�檺
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x000000, 1.0f, 0);
		Device->BeginScene();

		// �N���I�w�s�P�ƾڬy�j�w(�N�X���骺�H���ǿ��ø�s�y���u��)
		Device->SetStreamSource(0, g_VertexBuffer, 0, sizeof(stD3DVertex));
		// �]�w�F�����I�榡
		Device->SetFVF(D3DFVF_VERTEX);
		// �]�w�e�ϼҦ����u��
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
	// width must be 645+,�_�h�u����V���X��
	d3d::InitD3D(hinstance, 645, 480, true, D3DDEVTYPE_HAL, &Device);
	Setup();

	// �����`��
	d3d::EnterMsgLoop(Display);

	Cleanup();
	Device->Release();
}