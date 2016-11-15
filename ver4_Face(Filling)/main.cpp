#pragma region �Ұ���
// 
// ���ȫ�����Բ� ������ ������ �ø��ϴ�.
// 
// 
// DX ���α��� �����ϱ�
// main.cpp :
// 2016.07.21 kdh2183@gmail.com
#pragma endregion

// Include Header
#include <windows.h>
#include "Render.h"

#pragma region ��������
// ����������
HWND g_hWnd = NULL;
BOOL g_bLoop = TRUE;

int g_WindowWidth = 800;
int g_WindowHeight = 600;

char* g_ClassName = "SW-Rendering BFX";
extern char* g_WindowName;
#pragma endregion


//������ ���� ���� �Լ�
BOOL InitWindow(int width, int height);
void ResizeWindow(HWND hWnd, UINT NewWidth, UINT NewHeight);
INT MessagePump();

//�޽��� ó�� ���ν���
LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);
#pragma region CALLBACK(__stdcall) ����
////CALLBACK(__stdcall) �̶� ?
//���ڸ� �����ʿ��� �������� �ҷ��鿩 stack�� �״� ��
//��, �ǿ��ʿ� �ִ� ���ڰ� ���� ���� �ö�
//// __cdecl �� __stdcall �� ����(�� ������ ������)
// __cdel - �������ڸ� ������ ����,caller(�Լ��� ȣ���ϴ���)�� stack�� �����Ͽ� stack�� �����ϱ� ���� ��ɾ ���� �߰���
// __stdcall - �������ڸ� ������ ����,callee(�Լ� �ڽ�)�� stack�� �����Ѵ�. ���� ��ɾ �߰����� ����
//// ���ǻ���
// __stdcall�� �������� �������ڸ� ���� �� ����. OS�� ����ϴ� �Լ��� DLL������ __stdcall�� �����ϸ� ���

#pragma endregion

//////////////////////////////////////////////////////////////////////////
//WinMain : �����Լ�
//
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	//------------------------------------------------------------------//
	// �⺻���� ������ ������ ����..                                //
	//------------------------------------------------------------------//
	if (!InitWindow(g_WindowWidth, g_WindowHeight)) return 0;

	//------------------------------------------------------------------//
	// DX ���� ��ü �ʱ�ȭ                               //
	//------------------------------------------------------------------//
	//....
	RenderTargetCreate(g_hWnd);		//Back-Buffer : Render Target ����


	//------------------------------------------------------------------//
	// ������ �ε�                         //
	//------------------------------------------------------------------//
	if (!DataLoading())
	{
		g_bLoop = FALSE;
	}

	//------------------------------------------------------------------//
	// ���� ����                      //
	//------------------------------------------------------------------//
	while (g_bLoop) //������ �ε��� ���� ��
	{
		if (!MessagePump())  //�޼��� ���� - �޼����� ������ ����
			break;

		SceneRender(); //Rendering
	}

	//------------------------------------------------------------------//
	// ���ø����̼� ����                                        // 
	//------------------------------------------------------------------//
	DataRelease();				//������ ����.
	RenderTargetRelease();		//Back-Buffer : Render Target ����

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
// MsgProc :  ������ �޼��� ���ν���.
// 
LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//case WM_PAINT:
	//	{
	//		char* msg;
	//		PAINTSTRUCT rc;
	//		HDC hdc = BeginPaint(hwnd, &rc);
	//		SetTextColor(hdc, RGB(255, 255, 255));
	//		SetBkMode(hdc, TRANSPARENT); //��׶��� ��� ���� - �����ϰ�
	//		msg = "SoftWare Renderer Project";
	//		TextOut(hdc, 270, 250, msg, strlen(msg));
	//		msg = "Hello World!";
	//		TextOut(hdc, 350, 270, msg, strlen(msg));
	//		EndPaint(hwnd, &rc);
	//	}
	//	break;
	case WM_LBUTTONDOWN:
	{
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		LineUpdate(pt);
	}
	break;
	case WM_MOUSEMOVE: //��
	{
		//POINT pt; 
		g_VtxTemp.x = LOWORD(lParam);
		g_VtxTemp.y = HIWORD(lParam);
		//LineUpdate(pt);
	}
	break;
	case WM_RBUTTONDOWN://��
	{
		LineClear();			//��
	}
	break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hwnd, WM_DESTROY, 0, 0);
			break;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);

}

/////////////////////////////////////////////////////////////////////////////
//
// InitWindow  : ������ ���� �Լ�.
//
// width  : ������ ������ ���� ũ�� (pixel)
// height : ������ ������ ���� ũ�� (pixel)
//
// �Է¹��� ũ�⿡ ���߾� ������ ������ �����ϱ� ���ؼ� 
// Ŭ���̾�Ʈ ������ ���� ������ ��ü ũ�⸦ �������մϴ�.
//
#pragma region ������ ���α׷� ����
/*
2D(2 - Demensional)���� �̰� 3D �����̰� �����쿡���� ������ ���α׷����� �⺻���� �մϴ�.
���ϱ�� ? ����� �����մϴ�.���α׷��� ������ �ü�� ������ ���� �ϱ� ����

�׷��� �Ϲ����� ������ ���α׷��� ȭ�� ����� ���� ������ �ü���� �����ϴ� GDI��
����ϴµ� ���ӿ����� 2D�� 3D�� ǥ���ϱ� ���ؼ� �������� GDI�� �ݵ�� �̿������� �ʰ�
GDI���� ȭ�鿡 ���� ���� �׷��� �ڷ���� ǥ���� �� �ֵ��� �ϵ���� ������ �޴� �׷���
���̺귯���� �̿��մϴ�. ��ǥ���� �׷��� ���̺귯���� DirectX�� OpenGL

���̺귯���� ����Ϸ���, �� ��ǻ���� �޸𸮿� �����ϱ� ���ؼ� �� ������ �ڵ��� �ʿ��մϴ�.
�׷��� ������ ���α׷����� �⺻�� �Ǵ� ���Դϴ�.

������ ���α׷��� ����ؾ� �� �Լ��� ������� ���� ������ ������ ���α׷��� �޽���
����̶�� �Ͱ� 
GetMessage()�� PeekMessage() 
//GetMessage() - �޼����� ���������� ���
//PeekMessage() - �޼����� ���������� �������� ����
�Լ��� ������ ������ �� ����϶�� �̾߱� �ϰڽ��ϴ�.

�̷��� �ü���� �޽��� ������� �۵��� �ϴ� ������ ��ǻ�� �ڿ��� ȿ���� ���̱�
���ؼ� �Դϴ�. ���� ��� ������ �ϱ� ���� ��Ź�⸦ �����ٰ� �� �� ���� �� �� ������
��Ź�� �տ��� ������ �ִ� ���� �ƴ϶� ��Ź�� �۵���Ű�� ���� �Ѵٵ簡 û�Ҹ� �Ѵٵ簡
�ϴ� ���Դϴ�. �ƴϸ� ���Ŀ� �ɾƼ� ����ϰ� ���� �ִٰ� ������ �� ������ ��Ź�⿡��
���� ��ȣ�� �︮�� �� �� ��Ź�⸦ ���� ������ �ŵα⸸ �ϸ� �Ǵ� �� �ٷ� ������
�� �Ǿ��ٴ� ��ȣ�� ������ �ü�������� �޽����� �ش��� �˴ϴ�. �̷��� ���� ��ǻ�Ϳ�����
�۾�-�����ٸ�(Job-Scheduling)�̶�� �ϴµ� �� �� �ڼ��� ������ �ü�� ���� å����
���� �ϱ� �ٶ��ϴ�.

�׸��� ������ ���α׷����� �ڵ� �帧�� ���캻�ٸ�
������ ����� ���α׷� �ڵ�� ������ ���� ������ ����˴ϴ�.
main() �� ���α׷� �ڵ� ��� �� ������ Ŭ���� ��� �� ������ ����
�� Run �� ������ �Ҹ� �� ������ Ŭ���� ����

main() �� GetModuleHandle() �� RegisterClass() �� CreateWindow()
�� PeekMessage() or GetMessage() �� TranslateMessage() �� DispatchMessage()
�� WindowProcedure() �� DestroyWindow() �� UnRegisterClass()

< 1-1 ���α׷� �ڵ� ���>
�ܼ�(���� â�̶�� �����ϸ� �˴ϴ�.)��� ���α׷��̶�� GetModuleHandle()�̶��
�Լ��� �ʿ������� ������ ���α׷��̶�� WinMain(HINSTANCE hInst)����
GetModuleHandle() �Լ��� ������� �ʰ�, hInst �μ��� �̿��ϸ� �˴ϴ�.
(GetModuleHandle() �Լ��� HINSTANCE ���� ���غ��� hInst�� �����մϴ�.)
�׸��� WinMain�� ����ϸ� �ܼ� â�� ��������� �ʽ��ϴ�.


< 1-2 ������ Ŭ���� ���>
WNDCLASS ����ü�� �ν��Ͻ��� �����ϰ� �� �ν��Ͻ��� �����͸� ä���� RegisterClass()
�Լ��� ������ �ϸ� ������ Ŭ������ ����� �˴ϴ�. WNDCLASS �ν��Ͻ��� ���뿡�� ��
����ؾ� �� ���� �ִµ� className �� ������ �����츦 �����ϴ� CreateWindow �Լ�����
className�� �ݵ�� �����ؾ� �մϴ�. �׷��� ������ �����찡 ����� ������ ���� �ʽ��ϴ�.
���� �߿��� ���� ���� �ִµ� �ü���� ȣ���ϴ� ����� ���� �޽��� ó���Լ��� ��
�ν��Ͻ��� lpfnWndProc�Լ� �����Ϳ� �����ؾ� �ϴ� �͵� ���� ���ƾ� �մϴ�.


< 1-3 ������ ����>
������ Ŭ������ �ü���� ����� �ߴٸ� ���� �����츦 ���� �����Դϴ�. �������
CreateWindow() �Լ��� ����ϴ�. ��Ȥ CreateDialog() �Լ��� DialogBox() �Լ��� ���� ����
������ �� �Լ��� �� �忡���� ��������. CreateWindow() �Լ��� ������ ����� ���� �����Ѵٸ�
NULL �̿��� ���� ���� �ݴϴ�. �� ���� HWND���� �� �����Ͻñ� �ٶ��ϴ�.

CreateWindow() �Լ��� �����츸 ������� ȭ�鿡 ��� �������� �ʽ��ϴ�. �����츦 ȭ�鿡 ���̰�
�Ϸ��� ShowWindow(hWnd, SW_SHOW) �Լ��� ȣ���ؾ� �մϴ�. ���⼭ hWnd�� CreateWindow()�Լ���
������ ���Դϴ�.


< 1-4 �Լ��� �и�>
���� ����ó�� main()�Լ� �ȿ� �ڵ带 ���� �����ص� ���� ��� �����ϴ�. �׷��� �츮��
�ۼ��Ϸ��� �ϴ� ���α׷��� �ڵ� ���� �������� ���ʸ� �� �˴ϴ�. �̷� ���� �� �Լ� �ȿ�
����ٴ� ���� ���� �Ұ����� ���Դϴ�. �����ϴ��� �̰��� �õ��ϴ� ����� �����ϴ�. �׷���
������ �ڵ带 ����� �ͻӸ� �ƴ϶� ������ ����, �ڵ��� ���뿡�� �ٶ������� �ʱ�
�����Դϴ�.

���α׷��� ����� ���� ���� �Ϲ����� ��Ģ �߿� Divide and Conquer! (�����ؼ� �����϶�!)
��� �ݾ��� �����ϴµ� �̰��� �ϳ��� Ŀ�ٶ� ���α׷��� ������ ���� ������ ���α׷�
(�̰��� ����̶�� �մϴ�.)���� ����� ������ �մϴ�.

C������ �̰��� �Լ� ������ ���� �� �ֽ��ϴ�. �Լ��� ����� ���� � ������ ������
�Լ��� ���� ������ ��Ģ�� �־�� �մϴ�.
������ ������ ����(Create) �� ������ ����(Run) �� ������ �Ҹ�(Cleanup) �� �κ����� �����
�Լ��� ����� ���ô�.
���� ������ ���� Create() �Լ��� ��� ������ ������ �� ������ �����Ƿ� ������(int) ��ȯ��
�ϵ��� �ϰ� ������ 0, ������ ��� -1�� ��ȯ�ϵ��� �մϴ�. Run() �Լ��� ������ ��ȯ�� �־
���鵵�� �մϴ�. Cleanup() �Լ��� �������� ���� �κ������� ���� ������ ������ ��ȯ��
�ʿ䰡 ��� void�� �մϴ�.
*/
#pragma endregion

BOOL InitWindow(int width, int height)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC; //������ : http://m.blog.naver.com/bastard9/140114813809
	wc.lpfnWndProc = MsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = ::GetModuleHandle(NULL);
	wc.hCursor = NULL;	
	wc.hIcon = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_ClassName;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);
	
	//������ ����
	HWND hWnd = ::CreateWindow(
		g_ClassName,
		g_WindowName,
		//WS_OVERLAPPEDWINDOW, 		
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, //������ ��Ÿ��
		//WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
		0, //������ ���� x ��ǥ
		0, //������ ���� y ��ǥ
		width, height,
		GetDesktopWindow(),//�θ� ������
		NULL, //�޴� �ڵ�
		wc.hInstance, // �ν��Ͻ� �ڵ�
		NULL // lparam �� ���� ������
	);
	if (hWnd == NULL) return FALSE;

	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd); // ȭ�� �ٽ� ����

	//������ �ڵ� �������� ����
	g_hWnd = hWnd;

	//Ŭ���̾�Ʈ ���� ũ�� ������ : �ʼ�,��������
	ResizeWindow(hWnd, width, height);

	return TRUE;

}


/////////////////////////////////////////////////////////////////////////////
// 
// int MessagePump() : ������ �޼��� ó�� �Լ�.
//
// ���� ���� �޼��� ó���� ���ؼ� �޼��� ������ �����Ѵ�            
// ��������(OS)�κ��� �� ���ø����̼����� Ư���� �޼����� �������  
// �ʴ´ٸ�  ������ ���� �ϵ��� �մϴ�.                               
// ���Ŀ� �ѹ��� ������ �� ����.    
INT MessagePump()
{
	MSG msg; ::ZeroMemory(&msg, sizeof(msg));

	while (1)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//�޼��� ť�� �޼����� ������ ó��
		{
			if (msg.message == WM_QUIT) //������ ���Ḧ ���� ����
				return FALSE;

			//������ �޼��� ó��
			::TranslateMessage(&msg); //Ű���� �޽��� �߻��� �޽���(WM_CHAR)�� ����� ���� 
			::DispatchMessage(&msg); //�޽��� ť���� ���� �޽����� �������� �޽��� ó��(WndProc)�Լ��� ����
		}
		else//�޼����� ���ٸ� ����(������)�� ����
		{
			return TRUE;
		}
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////
//
// void B3D_ResizeWindow(UINT NewWidth, UINT NewHeight)
//
// â����� ��� �ػ� ����� ���߾� ��ü ������ ũ�⸦ �������մϴ�. 
// ex)
//'Ŭ���� ��Ʈ'������ 640 * 480 �� ���߾�  ��ü �������� ũ�⸦ 
// �ٽ� �����մϴ�. --> �׷��� '���� �̹���'�� ��� ȭ�鿡 ���δ�.
//
// ��  �� :  Ŭ���̾�Ʈ ������ ũ�� - NewWidth, NewHeight
// ���ϰ� :  ����. 
void ResizeWindow(HWND hWnd, UINT NewWidth, UINT NewHeight)
{
	//���� �������� ��Ÿ�� ���ϱ�
	RECT oldrc;
	DWORD sytle = (DWORD) ::GetWindowLong(hWnd, GWL_STYLE);		//������ ��Ÿ���� �������
	DWORD exstyle = (DWORD) ::GetWindowLong(hWnd, GWL_EXSTYLE); //Ȯ��� ������ ��Ÿ���� �������

	//���� ������ '��ü'ũ�� (��ũ����ǥ) �� ��´�
	::GetWindowRect(hWnd, &oldrc);

	//���� ������ �������� 'Ŭ���̾�Ʈ' ���� ũ�� ����ϱ�
	RECT newrc;
	newrc.left = 0;
	newrc.top = 0;
	newrc.right = NewWidth;
	newrc.bottom = NewHeight;

	//newrc ��ŭ�� Ŭ���̾�Ʈ ������ �����ϴ� ������ '��ü' ũ�⸦ ���մϴ�.
	//���� '�޴�' �� ���ٴ� �����Ͽ� ó���ǰ� ����.
	//���� ����� newrc �� �ٽ� ���´�. ( ��ũ�� ��ǥ )
	//exstyle &= ~WS_EX_TOPMOST;
	::AdjustWindowRectEx(&newrc, sytle, NULL, exstyle); //������ ũ�����

	//������ �������� �ʺ�� ���� ���մϴ�. 
	int width = (newrc.right - newrc.left);
	int height = (newrc.bottom - newrc.top);

	//���ο� ũ�⸦ �����쿡 �����մϴ�.
	::SetWindowPos(hWnd, HWND_NOTOPMOST,
		oldrc.left, oldrc.top,
		width, height, SWP_SHOWWINDOW);
}


//////////////////////end