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

char* g_WindowName = "B3Yena SW-Renderer 00 : LIne";




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

DWORD g_PtCheck = PT_NONE_;

//���ȭ�� DC (RenderTarget)
HDC g_hDC;


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
		MoveToEx(g_hDC, g_Sp.x, g_Sp.y, NULL);
		LineTo(g_hDC, g_Ep.x, g_Ep.y);
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
	MoveToEx(g_hDC, pt.x - 5, pt.y, NULL);
	LineTo(g_hDC, pt.x + 5, pt.y);

	MoveToEx(g_hDC, pt.x, pt.y - 5, NULL);
	LineTo(g_hDC, pt.x, pt.y + 5);
}

////////////////////////////////////////////////////////////////////////////// 
//
// ��� �׸��� ����. : �������� �ʿ��� (����̽���) ���� �۾��� ����.
//
void BegineScene()
{
	g_hDC = GetDC(g_hWnd);
	SetBkMode(g_hDC, TRANSPARENT);
}


////////////////////////////////////////////////////////////////////////////// 
//
// ��� �׸��� ����. : �������� �ʿ��� (����̽���) ���� �۾��� ����.
//
void EndScene()
{
	ReleaseDC(g_hWnd, g_hDC);
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
	FillRect(g_hDC, &rc, hBrush);
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

	//Sleep(5);		//--> ������ ������..����..
}


/////////////////////////////////////////////////////////////////////////////
//
// �ʴ� �����Ӽ� ���.
//
// ���� : int x, y : ����� ȭ�� ��ǥ.
//
void PutFPS(int x, int y)
{
	HDC hdc = g_hDC;

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

////////////////////////////////////////////////////////////////////////////// 
//
//  ����. 
//
void ShowHelp()
{
	int x = 5, y = 5;
	char msg[512];

	PutFPS(x, y);

	SetTextColor(g_hDC, RGB(255, 255, 255));
	//SetBkMode(hdc, TRANSPARENT);

	sprintf(msg, "�� Software Renderer \" B3Yena \" : Line Drawing");
	TextOut(g_hDC, x, y += 16, msg, strlen(msg));

	sprintf(msg, "�� 2���� �̿��� ���� �׸���");
	TextOut(g_hDC, x, y += 16, msg, strlen(msg));

	sprintf(msg, "��ǥ�Է� : L-Button");
	TextOut(g_hDC, x, y += 16, msg, strlen(msg));

	sprintf(msg, "Sp = {%d, %d}", g_Sp.x, g_Sp.y);
	TextOut(g_hDC, x, y += 16, msg, strlen(msg));

	sprintf(msg, "Ep = {%d, %d}", g_Ep.x, g_Ep.y);
	TextOut(g_hDC, x, y += 16, msg, strlen(msg));

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
		Clear(RGB(128, 128, 128));
		LineDraw();
		ShowHelp();
	}
	EndScene();

	// ��� ���...
	// ... 
	Present();
}






/****************** end of file "Render.cpp" *********************************/