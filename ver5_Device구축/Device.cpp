//
// Device.cpp :�⺻ ������ �� ����̽� ����/���� �ҽ�.
//
// B3Yena S/W Renderer ver.1.0 
//
//
//
#include "windows.h"
#include "mmsystem.h"
#include "stdio.h"


#include "Device.h"

/////////////////////////////////////////////////////////////////////////////
//
// ����̽� ���� ���� �����͵�. 
//


// ������ ����̽� ���� ������.
LPB3YENA g_pB3Y = NULL;					//��
LPB3YENADEVICE9  g_pDevice = NULL;		//��

//����� ����...
#define  hRT   g_pDevice->GetRT()

// ȭ�� ��� ���� ���� ����.  
//
YENADISPLAYMODE g_Mode = { 800, 600 }; //��

// �ý��� ��Ʈ.
HFONT g_hSysFont = NULL;
COLORREF g_SysFnColor = RGB(0, 255, 0);	//�⺻ �ý��� ��Ʈ ����.

/////////////////////////////////////////////////////////////////////////////
//
// ��Ÿ ���� ������. 
//
BOOL g_ShowFrame = FALSE;


/////////////////////////////////////////////////////////////////////////////
//
// ������ ���� �� ���� ��Ÿ ���� ���� : "���� �¾�" �� �ѹ��� ȣ��.
//               
int YenaSetup(HWND hwnd)
{

	// ���� ����.��
	//
	g_pB3Y = B3YenaCreate9(YENA_VERSION);
	if (YN_INVALIED(g_pB3Y))
	{
		//Error...
		return YN_FAIL;
	}


	// ���÷��� ���� ����.
	YENAPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	pp.Width = g_Mode.Width;		//�ػ� ����.(����� ũ��)
	pp.Height = g_Mode.Height;
	pp.BackBuffercnt = 1;			//����� ����. (����� 1���� ����)
	pp.Windowed = TRUE;				//Ǯ��ũ��, â��� ����.(����� â��常 ����)



	// ������ ���� ������ ����̽� ���� : DX9 ������	
	//
	g_pB3Y->CreateDevice(g_hWnd,				//����̽��� ������ ��ǥ ������ �ڵ�.
		&pp,									//����̽� ȭ�� ���� ����.
		YENACREATE_SOFTWARE_VERTEXPROCESSING,   //�������� ��� ���� (����� SW �� ����)
		&g_pDevice								//������ ���Ϲ��� ����̽� ��ü ������.
	);

	if (YN_INVALIED(g_pDevice))
	{
		//Error..
		return YN_FAIL;
	}


	// ����̽� �⺻ ���� �ɼ� ����.
	// ...
	// ...



	// �ý��� ��Ʈ ����.
	//
	g_hSysFont = CreateFont(
		12, 6,
		0, 0, 1, 0, 0, 0,
		DEFAULT_CHARSET,	//HANGUL_CHARSET  
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FF_DONTCARE,
		(LPSTR)"����"
	);
	if (g_hSysFont == NULL)
	{
		// error..! 
		return YN_FAIL;
	}
	SelectObject(hRT, g_hSysFont);



	return YN_OK;

}

/////////////////////////////////////////////////////////////////////////////
//
// "����" ���� ���� : ���ø����̼� ����� �ѹ��� ȣ��.
//
void YenaRelease()
{
	// ��Ʈ ����.
	DeleteObject(g_hSysFont);


	// ������ ��ü�� ����. 
	// ������ �������� �����ؾ� �˴ϴ� 
	// (�׷��� �ǵ��� ����Ǿ��� �����մϴ�.)
	//..
	SAFE_DELETE(g_pDevice);	//����̽� ���š�
	SAFE_DELETE(g_pB3Y);	//���� ���š� 

}

/////////////////////////////////////////////////////////////////////////////
//
// �ʴ� �����Ӽ� ���.
//
// ���� : int x, y : ����� ȭ�� ��ǥ.
//
void PutFPS(int x, int y)
{
	HDC hdc = hRT;

	static int frm = 0;
	static UINT oldtime = GetTickCount();
	static UINT frmcnt = 0;
	static float  fps = 0.0f;

	++frmcnt;

	char msg[80];
	int time = GetTickCount() - oldtime;
	if (time >= 999)						// 0~999 �и�������.. 1~1000�� �ƴ�
	{
		oldtime = GetTickCount();

		//1�ʰ� ������ ������ ���� ���մϴ�..
		frm = frmcnt;	frmcnt = 0;

		//�ʴ� ������ ���� ����մϴ�.
		fps = (float)(frm * 1000) / (float)time;
	}

	SetTextColor(hRT, g_SysFnColor);
	sprintf(msg, "fps=%.1f/%d    ", fps, time);
	TextOut(hdc, x, y, msg, strlen(msg));

}

/////////////////////////////////////////////////////////////////////////////
//
// ���� ����ȭ�� ����ð� ȹ��.
//
float GetEngineTime()
{
	static int oldtime = GetTickCount();
	int nowtime = GetTickCount();
	float dTime = (nowtime - oldtime) * 0.001f;
	oldtime = nowtime;

	return dTime;
}

/////////////////////////////////////////////////////////////////////////////
//
// ���ڿ� ���  
//
int DrawText(int x, int y, COLORREF col, char* msg, ...)
{
	va_list vl;
	char buff[4096] = "";
	va_start(vl, msg);
	vsprintf(buff, msg, vl);
	RECT rc = { x, y, x + 800, y + 600 };

	SetTextColor(hRT, col);
	int res = DrawText(hRT, buff, strlen(buff), &rc, DT_WORDBREAK);
	SetTextColor(hRT, g_SysFnColor);

	return res;
}




/*********************** end of file "Device.cpp" *********************/
