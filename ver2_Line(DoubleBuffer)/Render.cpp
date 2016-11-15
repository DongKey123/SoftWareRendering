//
// Render.cpp
#include "Windows.h"  
#include "Render.h"
#include "stdio.h"

#pragma warning(disable:4996)
/*
VS2005 ���ʹ� CRT ���̺귯�� �Լ��� ���ڿ� �ٷ�� �Լ��� ��������
���� �Ű��� ����.
�׷��� ������ ���ڿ� �Լ��� _s�� �ٿ���
������ ���̸� �����ϵ��� �����ϰ� �ִµ� �̰� ������
������ strcpy ���� ���ڿ� �Լ����� C4996 warning �� �߻��Ѵ�.
--> ��� ����
*/

char* g_WindowName = "B3Yena SW-Renderer 00 : LIne (+BackBuffer)";




/////////////////////////////////////////////////////////////////////////////
// 
// �߰� ������ �� ������ ���⿡... 

// ������ ����/��
POINT g_Sp, g_Ep;

enum {
	PT_NONE_ = 0x00,				//������ �� ����
	PT_SP_	= 0x01,					//1��° �� ������.
	PT_EP_	= 0x02,					//2��° �� ������.

	PT_COMPLETED_ = (PT_SP_|PT_EP_)	//�� �Է� �Ϸ�.--> ���� �׸���
};

DWORD g_PtCheck = PT_NONE_; //2���� ���� ��� �����Ǿ����� Ȯ�ο� ����

//���ȭ�� DC (RenderTarget)
HDC g_hDC;

// ����Ÿ��(RenderTarget : Back-Buffer) ������ �ڵ�.//��
//
HBITMAP g_hBmpRT = NULL;				
HDC		g_hSurfaceRT = NULL;			
COLORREF g_BkColor = RGB(0, 0, 255);
#define  g_hRT   g_hSurfaceRT

#pragma region ���� ���۸� ����
/*
1. ���� ���� ���̺귯��
=> ��������� ������ ���� ���� ���̺귯���� �������ִ�.
KERNEL : �޸𸮸� �����ϰ� ���α׷��� �����Ű�� ���̺귯��
USER : ���� �������̽��� �����츦 �����ϴ� ���̺귯��
GDI : ȭ��ó���� �׷����� ����ϴ� ���̺귯��

2.DC�� Device Context�� ���ڷ� ��¿� ���� ��� ������ ������ ������ ����ü
�� DC�� �׸��⿡ �ʿ��� �پ��� �������� ����� ������ ��
GDI ��⿡ ���� �����ǰ� �׸��� �Լ����� �����ϴ� ���̴�.

3.���� ���۸�
hdc�� �ѷ��� ������ ȭ�� -> ������ �׷��� �̹����� BackDC�� �ӽ� ���� 
-> BackDC�� ������ MemDC�� �����Ѵ�. -> MemDC�� ������ hdc�� �ѱ��. -> 
hdc���� ȭ�鿡 �ѷ��ش�.

*/
#pragma endregion



/////////////////////////////////////////////////////////////////////////////
//
int DataLoading()
{

	//�߰� �ڵ�� ���⿡...
	//...
	g_Sp.x = 0; g_Sp.y = 0;
	g_Ep.x = 0; g_Ep.y = 0;

	g_PtCheck = PT_NONE_;


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
//
void DataRelease()
{
	//������ ���� �ڵ��� �߰��� ���⿡..
	//...  

}

////////////////////////////////////////////////////////////////////////////// 
//
void LineUpdate(POINT pt)
{
	switch (g_PtCheck)
	{
		//�ʱ� ���� ������ ���..
	case PT_NONE_:
		//�Է¿Ϸ��� ���� �Է��� ���..
	case PT_COMPLETED_:
		g_Sp = pt;   g_PtCheck = PT_SP_;			//1��° �Է� �Ϸ�.
		g_Ep.x = 0;  g_Ep.y = 0;
		break;

		//2��° �Է½�...
	case PT_SP_:
		g_Ep = pt;  g_PtCheck = PT_COMPLETED_;		//�Է� �Ϸ� ó��.
		break;
	}

}

////////////////////////////////////////////////////////////////////////////// 
//
void LineDraw()
{
	switch (g_PtCheck)
	{
	case PT_NONE_:		//�׸��� ����.
		break;

	case PT_SP_:
		CrossDraw(g_Sp);		//������ ǥ��.
		break;

	case PT_COMPLETED_:			//�Ϸ�. ��� �׸���.
		CrossDraw(g_Sp);
		MoveToEx(g_hRT, g_Sp.x, g_Sp.y, NULL);
		LineTo(g_hRT, g_Ep.x, g_Ep.y);
		CrossDraw(g_Ep);
		break;
	}
}

////////////////////////////////////////////////////////////////////////////// 
//
// ���ڼ� �׸��� : ���콺 Ŭ�� ��ġ
//
void CrossDraw(POINT pt)
{
	MoveToEx(g_hRT, pt.x - 5, pt.y, NULL);
	LineTo(g_hRT, pt.x + 5, pt.y);

	MoveToEx(g_hRT, pt.x, pt.y - 5, NULL);
	LineTo(g_hRT, pt.x, pt.y + 5);
}

////////////////////////////////////////////////////////////////////////////// 
//
// ��� �׸��� ����. : �������� �ʿ��� (����̽���) ���� �۾��� ����.
//
void BegineScene()
{
	//g_hDC = GetDC(g_hWnd); ȭ��DC ������. ����Ÿ���� ��� ���...��
	SetBkMode(g_hRT, TRANSPARENT);
}


////////////////////////////////////////////////////////////////////////////// 
//
// ��� �׸��� ����. : �������� �ʿ��� (����̽���) ���� �۾��� ����.
//
void EndScene()
{
	//ReleaseDC(g_hWnd, g_hDC); --> ȭ��DC ������. ����Ÿ���� ��� ���...��
}

////////////////////////////////////////////////////////////////////////////// 
//
// ����Ÿ�� Ŭ����.
//
void Clear(COLORREF col)
{
	HBRUSH hBrush = CreateSolidBrush(col);
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	FillRect(g_hRT, &rc, hBrush);
	DeleteObject(hBrush);
}

////////////////////////////////////////////////////////////////////////////// 
//
// RT (Render Target) �� ����(�������� ���scene)�� Front Buffer �� ���.
//
void Present()
{
	//Swap Chain �� Flip �ϴ� �Լ��� '�̸�'�� ������ ������...
	//���⼭�� �ܼ� ����ó����.. 
	//�ʹ� ���� �׸���� ���� �� ������ �ʴ´�.(�Ǵ� ���ڰŸ�Flickering..)
	//....

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	HDC hdc = GetDC(g_hWnd);
	BitBlt(hdc,0,0, rc.right, rc.bottom, g_hSurfaceRT, 0, 0, SRCCOPY);
	ReleaseDC(g_hWnd, hdc);

}


/////////////////////////////////////////////////////////////////////////////
//
// �ʴ� �����Ӽ� ���.
//
// ���� : int x, y : ����� ȭ�� ��ǥ.
//
void PutFPS(int x, int y)
{
	HDC hdc = g_hRT;

	static int frm = 0;
	static UINT oldtime = GetTickCount();
	static UINT frmcnt = 0;
	static float  fps = 0.0f;
	//static float evfps = 0;		//��� ������.

	++frmcnt;

	char msg[80];
	int time = GetTickCount() - oldtime;
	if (time >= 999) // 0~999 �и�������.. 1~1000�� �ƴ�
	{
		oldtime = GetTickCount();

		//1�ʰ� ������ ������ ���� ���մϴ�..
		frm = frmcnt;	frmcnt = 0;

		//�ʴ� ������ ���� ����մϴ�.
		fps = (float)(frm * 1000) / (float)time;
	}

	SetTextColor(hdc, RGB(255, 255, 255));
	sprintf(msg, "fps=%.1f/%d    ", fps, time);
	TextOut(hdc, x, y, msg, strlen(msg));

#pragma region GetTickCount����
	/*
	DWORD GetTickCount(VOID);
	=> OS������ ������ ������ �ð��� msec ������ �����ִ� �Լ��̴�. �ִ� 49.7�ϰ��� ī��Ʈ�� ������ �� �ִ�.
	*/
#pragma endregion

}

///////////////////////////////////////////////////////////////////////////////
//
//  ����ۿ� ����Ÿ���� ����.��
//
int RenderTargetCreate(HWND hwnd)
{
	RECT rc; GetClientRect(hwnd, &rc);
	HDC hdc = GetDC(hwnd);
	g_hSurfaceRT = CreateCompatibleDC(hdc);//����Ÿ��,DC �ڵ� ����(Surface)
										   //http://blog.naver.com/PostView.nhn?blogId=unbraid&logNo=29274684&redirect=Dlog&widgetTypeCall=true
	g_hBmpRT = (HBITMAP)CreateCompatibleBitmap(hdc, rc.right, rc.bottom);	//����Ÿ��,��Ʈ�� ����.
	SelectObject(g_hSurfaceRT, g_hBmpRT);
	ReleaseDC(hwnd, hdc);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// 
// ����Ÿ�� ����.��
//
void RenderTargetRelease()
{
	DeleteObject(g_hBmpRT);
	DeleteDC(g_hSurfaceRT);
}

/////////////////////////////////////////////////////////////////////////////
//
// ���ڿ� ��� ��   
//
int DrawText(int x, int y, COLORREF col, char* msg, ...)
{
	va_list vl;
	char buff[4096] = "";
	va_start(vl, msg);
	vsprintf(buff, msg, vl);
	RECT rc = { x, y, x + 800, y + 600 };

	SetTextColor(g_hRT, col);
	int res = DrawText(g_hRT, buff, strlen(buff), &rc, DT_WORDBREAK);
	SetTextColor(g_hRT, RGB(255, 255, 255));

	return res;
}

////////////////////////////////////////////////////////////////////////////// 
//
//  ����. 
//
void ShowHelp()
{
	static bool bShow = true;
	if (IsKeyUp(VK_F1)) bShow ^= true;

	PutFPS(1, 1);

	if (!bShow) return;


	// Today's Topic.	 
	int x = 1, y = 16;
	COLORREF col = RGB(255, 255, 255);
	DrawText(x, y, col, "�� %s", g_WindowName);
	DrawText(x, y += 16, col, "�� 2���� �̿��� ���� �׸���");
	DrawText(x, y += 16, col, "��ǥ�Է� : L-Button");


	DrawText(x, y += 16, col, "Sp = {%d, %d}", g_Sp.x, g_Sp.y);
	DrawText(x, y += 16, col, "Ep = {%d, %d}", g_Ep.x, g_Ep.y);

	y += 16;
	DrawText(x, y += 16, col, "����:F1");


	y += 100;
	char* msg =
		"������۸� : \"BackBuffer\" �߰�.\n"
		"�ӵ�/���ڰŸ� ��.";
	DrawText(x, y, RGB(255, 255, 0), msg);


}



////////////////////////////////////////////////////////////////////////////// 
//
// ��� �׸��� : 
//
void SceneRender()
{

	// ��� ���� 
	//
	// ���� ������: ���ΰ�, ����, ������ �̵�, �浹�˻� ���..
	// ...
	//
	// ���� ���� �̺�Ʈ,����,�������..
	// ...


	// ��� �׸���...
	// ....
	BegineScene();
	{
		Clear(RGB(0, 0, 255));
		LineDraw();
		ShowHelp();
	}
	EndScene();

	// ��� ���...
	// ... 
	Present();
}






/****************** end of file "Render.cpp" *********************************/