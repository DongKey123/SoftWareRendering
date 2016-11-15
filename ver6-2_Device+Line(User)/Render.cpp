//
// Render.cpp
#include "Windows.h"  
#include "Render.h"
#include "Device.h"
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

char* g_WindowName = "B3Yena SW-Renderer 01 : Device";

///////////////////////////////////////////////////////////////////////////// 
//
// ���� ���� �����͵�.
//

// ���� ���� : ���� ������ ������ ��ü. ��
//
LPB3YENAVERTEXBUFFER9 g_pVB = NULL;


// �������� ������ ����(VERTEX FORMAT) �� �����մϴ�.
// 2D �� { ��� ��ǥ(Screen), ���� } ���� ����.��
//
struct COLVTX
{
	float x, y;			//2D ȭ����ǥ.
};

// ���� ����(�԰�) ��
#define FVF_COLVTX (B3YFVF_XY)

int	InitVB();


/////////////////////////////////////////////////////////////////////////////
// 
// �߰� ������ �� ������ ���⿡... 
BOOL g_bWireFrame = FALSE;		//���̾� ������ ��� �÷���.��

// ������ ����/��
//POINT g_Sp, g_Ep;
//
//enum {
//	PT_NONE_	= 0x00,					//������ �� ����
//	PT_V0_		= 0x01,						//1��° �� ������.
//	PT_V1_		= 0x02,						//2��° �� ������.
//	PT_V2_		= 0x04,						//3��° �� ������.
//
//	PT_MAX_ = 3,							//�ﰢ�� �� ����.
//	PT_1_ = PT_V0_,							//1�� �Է� �Ϸ�.
//	PT_2_ = (PT_V0_ | PT_V1_),				//2�� �Է� �Ϸ�.(V0+V1)
//	PT_3_ = (PT_V0_ | PT_V1_ | PT_V2_),		//3�� �Է� �Ϸ�.(V0+V1+V2)
//
//	PT_COMPLETED_ = (PT_V0_ | PT_V1_ | PT_V2_)		//��� �� �Է� �Ϸ�.--> �ﰢ�� �׸���...��
//
//};
//
////�Էµ� �ﰢ�� ����(��ġ)...��
//POINT g_Vtx[PT_MAX_];
//POINT g_VtxClear = { 0,0 };
//POINT g_VtxTemp = { 0,0 }; //���� ����� �������� ( ���콺�̵��� �� ��� �ֽ�ȭ)
//
//DWORD g_PtCheck = PT_NONE_; //2���� ���� ��� �����Ǿ����� Ȯ�ο� ����
//
////���ȭ�� DC (RenderTarget)
//HDC g_hDC;
//
//// ����Ÿ��(RenderTarget : Back-Buffer) ������ �ڵ�.//��
////
//HBITMAP g_hBmpRT = NULL;				
//HDC		g_hSurfaceRT = NULL;			
//COLORREF g_BkColor = RGB(0, 0, 255);
//#define  g_hRT   g_hSurfaceRT
//
//#pragma region ���� ���۸� ����
///*
//1. ���� ���� ���̺귯��
//=> ��������� ������ ���� ���� ���̺귯���� �������ִ�.
//KERNEL : �޸𸮸� �����ϰ� ���α׷��� �����Ű�� ���̺귯��
//USER : ���� �������̽��� �����츦 �����ϴ� ���̺귯��
//GDI : ȭ��ó���� �׷����� ����ϴ� ���̺귯��
//
//2.DC�� Device Context�� ���ڷ� ��¿� ���� ��� ������ ������ ������ ����ü
//�� DC�� �׸��⿡ �ʿ��� �پ��� �������� ����� ������ ��
//GDI ��⿡ ���� �����ǰ� �׸��� �Լ����� �����ϴ� ���̴�.
//
//3.���� ���۸�
//hdc�� �ѷ��� ������ ȭ�� -> ������ �׷��� �̹����� BackDC�� �ӽ� ���� 
//-> BackDC�� ������ MemDC�� �����Ѵ�. -> MemDC�� ������ hdc�� �ѱ��. -> 
//hdc���� ȭ�鿡 �ѷ��ش�.
//
//*/
//#pragma endregion
//
////���� �׸��� �ҡ�
//HPEN g_hPenDash;
//HPEN g_hPenWhite;
//HPEN g_hPenGreen;
//
////�������� ����.��
//BOOL g_bShowVtxInfo = TRUE;



/////////////////////////////////////////////////////////////////////////////
//
int DataLoading()
{
	//�߰� �ڵ�� ���⿡...
	//...

	//�������� ����.��
	InitVB();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//
void DataRelease()
{
	//������ ���� �ڵ��� �߰��� ���⿡..
	//...  
}

///////////////////////////////////////////////////////////////////////////// 
//
// ���� ���� ���� �Լ�.��
//
int	InitVB()
{
	//�ﰢ���� ���� 3���� ���� ����. : ������ ��ǥ���� ȭ��(Screen)��ǥ.��
	COLVTX	Vertices[] = {

		//Face 0 : ���ﰢ��.��
		{ 50.0f, 250.0f },		//v0
		{ 150.0f,  50.0f },		//v1
		{ 250.0f, 250.0f },		//v2

								//Face 1 : ���ﰢ��.��
		{ 50.0f, 250.0f },
		{ 250.0f, 250.0f },
		{ 150.0f, 450.0f },

		//Face 2: ���� �ﰢ�� (CW) �׽�Ʈ �ﰢ�� ��
		{ 300.0f, 500.0f },
		{ 400.0f, 300.0f },
		{ 480.0f, 430.0f },

		//Face 3: ���� �ﰢ�� (CCW) �׽�Ʈ �ﰢ�� ��
		{ 500.0f, 430.0f },
		{ 600.0f, 300.0f },
		{ 680.0f, 500.0f },

		//Face 4 : ���� �ﰢ1��
		{ 10.0f,  30.0f },		//v0
		{ 10.0f, 100.0f },		//v1
		{ 60.0f, 100.0f },		//v2

		//Face 5 : ���� �ﰢ2��
		{ 40.0f,   30.0f },		//v0
		{ 90.0f,  30.0f },		//v1
		{ 90.0f, 100.0f },		//v2

		//Face 6 : ���ﰢ��.��
		{ 750.0f, 550.0f },		//v0
		{ 650.0f, 550.0f },		//v1
		{ 750.0f, 450.0f },		//v2
								// */
	};



	//���� ���� ����.
	if (YN_FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(Vertices),			//'���� ����'�� ũ�� (����Ʈ)
		FVF_COLVTX,					//'����' �԰�.�� 
		B3YPOOL_SYSTEM,				//�ý��۸޸� ���. (����� �� �ɼǸ� ��ȿ) ��
		&g_pVB						// ������ ���ϵǴ� ���� �����ͤ�
	)))
	{
		return YN_FALSE;
	}

	//���� �ּ� ��� : ���� DX �� �װͰ��� ��Ȱ�� �ٸ�����, 
	//������ ����� �����մϴ�.
	VOID*	pBuff;
	if (YN_FAILED(g_pVB->Lock(0, (void**)&pBuff)))
	{
		return YN_FALSE;
	}

	//���ۿ� ���� ������ ä���.
	memcpy(pBuff, Vertices, sizeof(Vertices));

	//DX ������ �۾��Ϸ��� ȹ���� �ּ�/�޸��� ������ ����
	//Unlock �� �ؾ������� �츮�� �� ������ �����ϰڽ��ϴ�. 
	g_pVB->Unlock();


	//...�۾��Ϸ�...
	//...���� ������ ���� �������� �����ϸ� �ǰڽ��ϴ�.
	//...


	return YN_OK;

}



/////////////////////////////////////////////////////////////////////////////// 
//
void ObjDraw()
{

	//���� ���� ��� : DX �� �װͰ� ���ϸ� ���.
	g_pDevice->SetStreamSource(g_pVB, sizeof(COLVTX));

	//���� ���� ����.
	g_pDevice->SetFVF(FVF_COLVTX);

	//'���ϵ���' ������ : ���ݺ��� ��� �׸��Ⱑ ���۵˴ϴ�...
	// DX �޼ҵ�� (����)������ �ñ״���(Signature) �� �����ϴ� ���� ��ǥ�Դϴ�.��
	g_pDevice->DrawPrimitive(B3YPT_TRIANGLELIST, 0, 7);

}




//
//////////////////////////////////////////////////////////////////////////////// 
////
//// ��� �׸��� ���� �ʱ�ȭ...
////
//void LineClear()
//{
//	for (int i = 0; i < PT_MAX_; i++)
//	{
//		g_Vtx[i] = g_VtxClear;			//���� �ʱ�ȭ...  
//	}
//	g_VtxTemp = g_VtxClear;
//
//	g_PtCheck = PT_NONE_;
//}
//
//
//////////////////////////////////////////////////////////////////////////////// 
////
//void LineUpdate(POINT pt)
//{
//	switch (g_PtCheck)
//	{
//		//�ʱ� ���� ������ ���..
//	case PT_NONE_:
//		//�Է¿Ϸ��� ���� �Է��� ���..
//	case PT_COMPLETED_:
//		g_Vtx[0] = pt;
//		g_Vtx[1] = g_VtxClear;
//		g_Vtx[2] = g_VtxClear;
//		g_PtCheck = PT_1_;			//1��° �Է� �Ϸ�.��
//		break;
//
//		//2��° �Է½�...
//	case PT_1_:
//		g_Vtx[1] = pt;
//		g_PtCheck = PT_2_;			//2��° �Է� �Ϸ�.��
//		break;
//
//		//3��° �Է½�..
//	case PT_2_:
//		g_Vtx[2] = pt;
//		g_PtCheck = PT_COMPLETED_;		//�Է� �Ϸ� ó��.
//		break;
//	}
//
//}
//
//////////////////////////////////////////////////////////////////////////////// 
////
//void LineDraw()
//{
//	switch (g_PtCheck)
//	{
//	case PT_NONE_:		//�׸��� ����.
//		break;
//
//	case PT_1_:
//		CrossDraw(g_Vtx[0], "v0");			//ù��° ǥ��.
//
//		LineDashDraw(g_Vtx[0], g_VtxTemp);	//�ӽö��� ǥ��..(�⼱)		
//		break;
//
//	case PT_2_:
//		CrossDraw(g_Vtx[0], "v0");		//ù��° ǥ��.
//		CrossDraw(g_Vtx[1], "v1");		//ù��° ǥ��.
//
//		LineDashDraw(g_Vtx[0], g_VtxTemp);	//�ӽö��� ǥ��..(�⼱)
//		LineDashDraw(g_Vtx[1], g_VtxTemp);	//�ӽö��� ǥ��..(�⼱)
//
//		LineDraw(g_Vtx[0], g_Vtx[1]);	//���� �׸��� : V0 -> V1
//
//		break;
//
//	case PT_COMPLETED_:			//�Ϸ�. ��� �׸���.
//
//		if (g_bShowVtxInfo)		//���� ���� ���..
//		{
//			for (int i = 0; i < PT_MAX_; i++)
//				CrossDraw( g_Vtx[i], "v%d", i);
//		}
//
//		FaceDraw();  			//�ﰢ�� �׸���..
//
//		break;
//	}
//}
//
//
//////////////////////////////////////////////////////////////////////////////// 
////
//// ���� �׸��� : sp -> ep //GDI�� �ƴ� SetPixel�� �������� �� �׸���
////
//void LineDraw(POINT sp, POINT ep)
//{
//	int X = ep.x - sp.x;  //x���� ���� Ȯ��.
//	int Y = ep.y - sp.y;  //y���� ���� Ȯ��.
//						  ///////////////////////////////////
//						  //abs() -> ������ ���밪 ����.
//						  ///////////////////////////////////
//
//						  //�� ��� ó��.////////////////////
//	int steps = max(abs(X), abs(Y));
//	///////////////////////////////////
//
//	float x_incre = (float)X / (float)steps;
//	float y_incre = (float)Y / (float)steps;
//
//	float x = (float)sp.x;
//	float y = (float)sp.y;
//
//	for (int k = 0; k <= steps; k++)
//	{
//		x = x + x_incre;
//		y = y + y_incre;
//		SetPixel(g_hRT, (int)x, (int)y, RGB(0, 0, 0));
//	}
//	/*MoveToEx(g_hRT, sp.x, sp.y, NULL);
//	LineTo(g_hRT,  ep.x, ep.y);*/
//}
//
//
//
//////////////////////////////////////////////////////////////////////////////// 
////
//// �⼱(�ӽö���) �׸��� : sp -> ep
////
//void LineDashDraw(POINT sp, POINT ep)
//{
//	HPEN hOldPen = (HPEN)SelectObject(g_hRT, g_hPenDash);
//	MoveToEx(g_hRT, sp.x, sp.y, NULL);
//	LineTo(g_hRT, ep.x, ep.y);
//	SelectObject(g_hRT, hOldPen);
//}
//
//void SortVert(POINT* v0, POINT* v1, POINT* v2)
//{
//	
//}
//
//
//
//////////////////////////////////////////////////////////////////////////////// 
////
//// �ﰢ�� �׸���.
////
//void FaceDraw()
//{
//	////���� �׸���.. : v0->v1
//	//LineDraw(g_Vtx[0], g_Vtx[1]);
//
//	////���� �׸���.. : v0->v2
//	//LineDraw(g_Vtx[0], g_Vtx[2]);
//
//	////���� �׸���.. : v1->v2
//	//LineDraw(g_Vtx[1], g_Vtx[2]);
//
//	FaceDraw(g_Vtx[0], g_Vtx[1], g_Vtx[2]);
//
//}
//
//void FaceDraw(POINT v0, POINT v1, POINT v2)
//{
//
//
//	POINT ver0, ver1, ver2;
//
//	if (v0.y > v1.y)
//	{
//		if (v1.y > v2.y)
//		{
//			ver0 = v2;
//			ver1 = v1;
//			ver2 = v0;
//		}
//		else
//		{
//			if (v2.y > v0.y)
//			{
//				ver0 = v1;
//				ver1 = v0;
//				ver2 = v2;
//			}
//			else
//			{
//				ver0 = v1;
//				ver1 = v2;
//				ver2 = v0;
//			}
//		}
//	}
//	else
//	{
//		if (v0.y > v2.y)
//		{
//			ver0 = v2;
//			ver1 = v0;
//			ver2 = v1;
//		}
//		else
//		{
//			if (v2.y > v1.y)
//			{
//				ver0 = v0;
//				ver1 = v1;
//				ver2 = v2;
//			}
//			else
//			{
//				ver0 = v0;
//				ver1 = v2;
//				ver2 = v1;
//			}
//		}
//	}
//
//	if ( ver0.y == ver1.y || ver1.y == ver2.y || ver0.y == ver2.y)
//	{
//		if (ver1.y == ver2.y)
//		{
//			//���ﰢ��
//			if (ver1.x < ver2.x)
//			{
//				POINT temp;
//				temp = ver1;
//				ver1 = ver2;
//				ver2 = temp;
//			}
//			float left_incre = (float)(ver0.x - ver2.x) / (float)(ver0.y - ver2.y);
//			float right_incre = (float)(ver0.x - ver1.x) / (float)(ver0.y - ver1.y);
//			float startX = ver0.x;
//			float endX = ver0.x;
//			for (int spY = ver0.y; spY <= (int)ver1.y; ++spY)
//			{
//				startX += left_incre;
//				endX += right_incre;
//				int spX = (int)startX;
//				int epX = (int)endX;
//				for (; spX <= epX; spX++)
//				{
//					SetPixel(g_hRT, spX, spY, RGB(0, 0, 0));
//				}
//			}
//		}
//		if (ver1.y == ver0.y)
//		{
//			//�Ʒ� �ﰢ��
//			if (ver1.x < ver0.x)
//			{
//				POINT temp;
//				temp = ver1;
//				ver1 = ver0;
//				ver0 = temp;
//			}
//			float left_incre = (float)(ver0.x - ver2.x) / (float)(ver0.y - ver2.y);
//			float right_incre = (float)(ver1.x - ver2.x) / (float)(ver1.y - ver2.y);
//			float startX = ver0.x;
//			float endX = ver1.x;
//			for (int spY = ver1.y; spY <= (int)ver2.y; ++spY)
//			{
//				startX += left_incre;
//				endX += right_incre;
//				int spX = (int)startX;
//				int epX = (int)endX;
//				for (; spX <= epX; spX++)
//				{
//					SetPixel(g_hRT, spX, spY, RGB(0, 0, 0));
//				}
//			}
//		}
//	}
//	else if (IsCW(ver0.x,ver0.y,ver1.x,ver1.y,ver2.x,ver2.y) == 1 )
//	{
//
//
//		//���ﰢ��
//		float left_incre = (float)(ver0.x - ver2.x) / (float)(ver0.y - ver2.y);
//		float right_incre = (float)(ver0.x - ver1.x) / (float)(ver0.y - ver1.y);
//		float startX = ver0.x;
//		float endX = ver0.x;
//		for (int spY = ver0.y; spY <= (int)ver1.y; ++spY)
//		{
//			startX += left_incre;
//			endX += right_incre;
//			int spX = (int)startX;
//			int epX = (int)endX;
//			for (; spX <= epX; spX++)
//			{
//				SetPixel(g_hRT,spX, spY, RGB(0, 0, 0));
//			}
//		}
//		//�Ʒ� �ﰢ��
//		right_incre = (float)(ver2.x - ver1.x) / (float)(ver2.y - ver1.y);
//		for (int spY = ver1.y; spY <= (int)ver2.y; ++spY)
//		{
//			startX += left_incre;
//			endX += right_incre;
//			int spX = (int)startX;
//			int epX = (int)endX;
//			for (; spX <= epX; spX++)
//			{
//				SetPixel(g_hRT, spX, spY, RGB(0, 0, 0));
//			}
//		}
//	}
//	else if (IsCW(ver0.x, ver0.y, ver1.x, ver1.y, ver2.x, ver2.y) == -1)
//	{
//		//���ﰢ��
//		float left_incre = (float)(ver0.x - ver1.x) / (float)(ver0.y - ver1.y);
//		float right_incre = (float)(ver0.x - ver2.x) / (float)(ver0.y - ver2.y);
//		float startX = ver0.x;
//		float endX = ver0.x;
//		for (int spY = ver0.y; spY <= (int)ver1.y; ++spY)
//		{
//			startX += left_incre;
//			endX += right_incre;
//			int spX = (int)startX;
//			int epX = (int)endX;
//			for (; spX <= epX; spX++)
//			{
//				SetPixel(g_hRT, spX, spY, RGB(0, 0, 0));
//			}
//		}
//		//�Ʒ� �ﰢ��
//		left_incre = (float)(ver2.x - ver1.x) / (float)(ver2.y - ver1.y);
//		for (int spY = ver1.y; spY <= (int)ver2.y; ++spY)
//		{
//			startX += left_incre;
//			endX += right_incre;
//			int spX = (int)startX;
//			int epX = (int)endX;
//			for (; spX <= epX; spX++)
//			{
//				SetPixel(g_hRT, spX, spY, RGB(0, 0, 0));
//			}
//		}
//	}
//
//
//	//int X = v0.x - v1.x;  //x���� ���� Ȯ��.
//	//int Y = v0.y - v1.y;  //y���� ���� Ȯ��.
//	//					  ///////////////////////////////////
//	//					  //abs() -> ������ ���밪 ����.
//	//					  ///////////////////////////////////
//
//	//					  //�� ��� ó��.////////////////////
//	//int steps = max(abs(X), abs(Y));
//	/////////////////////////////////////
//
//	//float x_incre = (float)X / (float)steps;
//	//float y_incre = (float)Y / (float)steps;
//
//	//float x = (float)v0.x;
//	//float y = (float)v0.y;
//
//	//for (int k = 0; k <= steps; k++)
//	//{
//	//	x = x + x_incre;
//	//	y = y + y_incre;
//	//	SetPixel(g_hRT, (int)x, (int)y, RGB(0, 0, 0));
//	//}
//}
//
//
//////////////////////////////////////////////////////////////////////////////// 
////
//// ���ڼ� �׸��� : ���콺 Ŭ�� ��ġ
////
//void CrossDraw(POINT pt, char* name, ...)
//{
//	HPEN hOldPen = (HPEN)SelectObject(g_hRT, g_hPenGreen);
//
//	MoveToEx(g_hRT, pt.x - 5, pt.y, NULL);
//	LineTo(g_hRT, pt.x + 5, pt.y);
//
//	MoveToEx(g_hRT, pt.x, pt.y - 5, NULL);
//	LineTo(g_hRT, pt.x, pt.y + 5);
//
//	va_list  vl;
//	char buff[80];
//	va_start(vl, name);
//	vsprintf(buff, name, vl);
//	//va_end(vl);
//	TextOut(g_hRT, pt.x, pt.y, buff, strlen(buff));
//
//	SelectObject(g_hRT, hOldPen);
//
//}
//
//////////////////////////////////////////////////////////////////////////////// 
////
//// ��� �׸��� ����. : �������� �ʿ��� (����̽���) ���� �۾��� ����.
////
//void BegineScene()
//{
//	//g_hDC = GetDC(g_hWnd); ȭ��DC ������. ����Ÿ���� ��� ���...
//	SetBkMode(g_hRT, TRANSPARENT);
//}
//
//
//////////////////////////////////////////////////////////////////////////////// 
////
//// ��� �׸��� ����. : �������� �ʿ��� (����̽���) ���� �۾��� ����.
////
//void EndScene()
//{
//	//ReleaseDC(g_hWnd, g_hDC); --> ȭ��DC ������. ����Ÿ���� ��� ���...
//}
//
//////////////////////////////////////////////////////////////////////////////// 
////
//// ����Ÿ�� Ŭ����.
////
//void Clear(COLORREF col)
//{
//	HBRUSH hBrush = CreateSolidBrush(col);
//	RECT rc;
//	GetClientRect(g_hWnd, &rc);
//	FillRect(g_hRT, &rc, hBrush);
//	DeleteObject(hBrush);
//}
//
//////////////////////////////////////////////////////////////////////////////// 
////
//// RT (Render Target) �� ����(�������� ���scene)�� Front Buffer �� ���.
////
//void Present()
//{
//	//Swap Chain �� Flip �ϴ� �Լ��� '�̸�'�� ������ ������...
//	//���⼭�� �ܼ� ����ó����.. 
//	//�ʹ� ���� �׸���� ���� �� ������ �ʴ´�.(�Ǵ� ���ڰŸ�Flickering..)
//	//....
//
//	RECT rc;
//	GetClientRect(g_hWnd, &rc);
//	HDC hdc = GetDC(g_hWnd);
//	BitBlt(hdc,0,0, rc.right, rc.bottom, g_hSurfaceRT, 0, 0, SRCCOPY);
//	ReleaseDC(g_hWnd, hdc);
//
//}
//
//
///////////////////////////////////////////////////////////////////////////////
////
//// �ʴ� �����Ӽ� ���.
////
//// ���� : int x, y : ����� ȭ�� ��ǥ.
////
//void PutFPS(int x, int y)
//{
//	HDC hdc = g_hRT;
//
//	static int frm = 0;
//	static UINT oldtime = GetTickCount();
//	static UINT frmcnt = 0;
//	static float  fps = 0.0f;
//	//static float evfps = 0;		//��� ������.
//
//	++frmcnt;
//
//	char msg[80];
//	int time = GetTickCount() - oldtime;
//	if (time >= 999) // 0~999 �и�������.. 1~1000�� �ƴ�
//	{
//		oldtime = GetTickCount();
//
//		//1�ʰ� ������ ������ ���� ���մϴ�..
//		frm = frmcnt;	frmcnt = 0;
//
//		//�ʴ� ������ ���� ����մϴ�.
//		fps = (float)(frm * 1000) / (float)time;
//	}
//
//	SetTextColor(hdc, RGB(255, 255, 255));
//	sprintf(msg, "fps=%.1f/%d    ", fps, time);
//	TextOut(hdc, x, y, msg, strlen(msg));
//
//#pragma region GetTickCount����
//	/*
//	DWORD GetTickCount(VOID);
//	=> OS������ ������ ������ �ð��� msec ������ �����ִ� �Լ��̴�. �ִ� 49.7�ϰ��� ī��Ʈ�� ������ �� �ִ�.
//	*/
//#pragma endregion
//
//}
//
/////////////////////////////////////////////////////////////////////////////////
////
////  ����ۿ� ����Ÿ���� ����
////
//int RenderTargetCreate(HWND hwnd)
//{
//	RECT rc; GetClientRect(hwnd, &rc);
//	HDC hdc = GetDC(hwnd);
//	g_hSurfaceRT = CreateCompatibleDC(hdc);//����Ÿ��,DC �ڵ� ����(Surface)
//										   //http://blog.naver.com/PostView.nhn?blogId=unbraid&logNo=29274684&redirect=Dlog&widgetTypeCall=true
//	g_hBmpRT = (HBITMAP)CreateCompatibleBitmap(hdc, rc.right, rc.bottom);	//����Ÿ��,��Ʈ�� ����.
//	SelectObject(g_hSurfaceRT, g_hBmpRT);
//	ReleaseDC(hwnd, hdc);
//
//	return TRUE;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// 
//// ����Ÿ�� ����
////
//void RenderTargetRelease()
//{
//	DeleteObject(g_hBmpRT);
//	DeleteDC(g_hSurfaceRT);
//}
//
///////////////////////////////////////////////////////////////////////////////
////
//// ���ڿ� ��� 
////
//int DrawText(int x, int y, COLORREF col, char* msg, ...)
//{
//	va_list vl;
//	char buff[4096] = "";
//	va_start(vl, msg);
//	vsprintf(buff, msg, vl);
//	RECT rc = { x, y, x + 800, y + 600 };
//
//	SetTextColor(g_hRT, col);
//	int res = DrawText(g_hRT, buff, strlen(buff), &rc, DT_WORDBREAK);
//	SetTextColor(g_hRT, RGB(255, 255, 255));
//
//	return res;
//}

/////////////////////////////////////////////////////////////////////////////// 
//
//  ����. 
//
void ShowInfo()
{
	static bool bShow = true;
	if (IsKeyUp(VK_F1)) bShow ^= true;

	if (!bShow)
	{
		//DrawText(1,20, D3DXCOLOR(1, 1, 0, 1), "[Help] F1"); 
		return;
	}


	// Today's Topic.
	{
		int x = 300, y = 50;
		COLORREF col = RGB(255, 255, 255);
		DrawText(x, y, col, "�� %s", g_WindowName);

		y += 24;
		char* msg =
			"1.����(Vertex) �� �����մϴ�.\n"
			"2.�ﰢ��(Face) �� �����մϴ�.\n"
			"3.���� ���� Ŭ������ �����մϴ�.\n"
			"4.�ﰢ���� ����(WireFrame) ���� �������մϴ�.\n"
			"\n"
			"\n< ���� ���� >\n"
			"5.�ﰢ�� ���θ� ���� �������� ä��ϴ� (FillMode).\n"
			"6.��������(Linear Interpolation) �� �����մϴ�.\n";

		DrawText(x, y, col, msg);
	}


	int x = 300, y = 300;
	static int cnt = 0;
	DrawText(x, y, RGB(255, 255, 0), "�� _DrawLine (ver. GDI)");

}




////////////////////////////////////////////////////////////////////////////// 
//
// ��� �׸��� : 
//
void SceneRender()
{

	//-------------------------------
	// ����/�ý��� ����.
	//------------------------------- 
	//���� ����ð� ���.
	//float dTime = GetEngineTime();


	// ��� ���� 
	//
	// ���� ������: ���ΰ�, ����, ������ �̵�, �浹�˻� ���..
	// ...
	// ���� ���� �̺�Ʈ,����,�������..
	// ...



	//-------------------------------
	// ��� �׸��� ����.. 
	//-------------------------------

	//��� �׸��� �غ�..
	g_pDevice->BeginScene();					//��
	{
		//����Ÿ��(���) �����..	
		g_pDevice->Clear(RGB(0, 0, 255));		//��	

		//..����, ������ �׸���..���..
		ObjDraw();


												//���� �� ��Ÿ ������ ���� ���.
		PutFPS(1, 1);
		ShowInfo();

	}
	//��� �׸��� ����...
	g_pDevice->EndScene();						//��


	//-------------------------------
	// ��� �׸��� ����.
	// 1ȸ�� ���� ���� ����.
	//------------------------------- 
	g_pDevice->Present();			//ȭ����� : Flip! ��

}






/****************** end of file "Render.cpp" *********************************/