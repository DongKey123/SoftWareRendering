#include "B3Yena.h"

/////////////////////////////////////////////////////////////////////////////// 
//
// B3YenaVertexBuffer : ���� ����.(DX9 ����)�� 
//
//
/////////////////////////////////////////////////////////////////////////////// 

B3YenaVertexBuffer9::B3YenaVertexBuffer9(void)
{
	m_pVBuffer = NULL;

	m_SizeInByte = 0;
	m_FVF = 0;
	m_Stride = 0;
}

B3YenaVertexBuffer9::~B3YenaVertexBuffer9(void)
{
	SAFE_DELARRY(m_pVBuffer);
}

///////////////////////////////////////////////////////////////////////////////
//
// ����ڰ� ������ �ɼ����� �������۸� ����.
//
int B3YenaVertexBuffer9::Create(UINT Length,		//'���� ����'�� ��ü ũ�� (����Ʈ)	
								DWORD FVF,			//'����' �԰�.�� 
								B3YENAPOOL Pool		//�ý��۸޸� ���. (����� �� �ɼǸ� ��ȿ) �� 
								)		//��
{
	//�̹� ������� �ִٸ� ����..����ڿ��� �ذ��� �䱸. 
	//���� �ڵ带 �߰��ϴ� ���� ��õ�մϴ�. ex) YN_ERR_NOTEMPTY
	if (YN_VALIED(m_pVBuffer)) return YN_FAIL;

	//PooL �ɼ��� �����մϴ�. : ���� DX �� �װ�ó�� ǥ���ϱ� ���� �뵵 �Դϴ�.
	//...

	m_pVBuffer = static_cast<void*>(new BYTE[Length]);
	m_SizeInByte = Length;
	m_FVF = FVF;

	//����1���� ũ��(����Ʈ) ����ϱ�.
	//������ �����԰�(FVF) �������� ����� ����.
	m_Stride = 0;
	if (CHECK(m_FVF, B3YFVF_XY))	 m_Stride += sizeof(float) * 2;		//2d ��ǥ.
	//if(CHECK(m_FVF, B3YFVF_DIFFUSE))  m_Stride += sizeof(DWORD);		//����

																		//���� üũ..
	if (m_Stride <= 0) {  /* Error!!...  */  return YN_FAIL; }

	return YN_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// ���� ���ۿ� '�����͸� �Է��ϱ� ���� �ش� �ּҸ� ���մϴ�.
//
// ��ü ������, �Ϻκ��� �ּҸ� ��� �͵� ����. 
// ���� DX �� �װͰ��� ��Ȱ�� �ٸ�����, ������ ����� �����մϴ�.��
//
int B3YenaVertexBuffer9::Lock( UINT OffsetToLock,		//[in]������ ���� ������ �ɼ� �ּ�. �⺻�� 0. 
							  void ** ppbData			//[out]���Ϲ��� ������.
							  )
{	
	if(YN_INVALIED(*ppbData)) return YN_FAIL;			//��ȿ�� �˻�.

	BYTE* pVB = (BYTE*)m_pVBuffer + OffsetToLock;		//���� �ּ� ���.

	*ppbData = (void*)pVB;								//�ּ� �ѱ�. 

	return YN_OK;
}

/////////////////////////////////////////////////////////////////////////////// 
//
// B3Yena ��ü ���� �ֻ��� ȣ�� �Լ�
//
/////////////////////////////////////////////////////////////////////////////// 
//
B3Yena* B3YenaCreate9(DWORD ver)
{
	B3Yena* pYena = new B3Yena;

	//���н� ����ó�� �ʿ�...
	//ASSERT(pYena);

	return pYena;
}

/////////////////////////////////////////////////////////////////////////////// 
//
// B3Yena SW Renderer : ���� ������ '����̽� Device' ���� ������ �ֻ��� Ŭ����
//
/////////////////////////////////////////////////////////////////////////////// 



B3Yena::B3Yena(void)
{
}

B3Yena::~B3Yena(void)
{
}


/////////////////////////////////////////////////////////////////////////////// 
//
// ���� ������ ����̽� ��ü ���� �޼ҵ�.
//
int B3Yena::CreateDevice(HWND hwnd,
	YENAPRESENT_PARAMETERS* pp,
	DWORD vp,
	LPB3YENADEVICE9* ppDevice
)
{
	//�Է� ���� Ȯ�� : �������� ���ϰ��� �ٸ��� �ϴ� ���� ��õ.
	if (hwnd == NULL) return YN_FAIL;
	if (pp == NULL) return YN_FAIL;
	if (ppDevice == NULL) return YN_FAIL;

	//����̽� ��ü ����. : �ܼ��ϰ� DX9 �� �����մϴ�.��
	LPB3YENADEVICE9 pDev = new B3YenaDevice9;

	//����̽� �ʱ�ȭ..
	pDev->m_hWnd = hwnd;
	pDev->m_PresentParam = *pp;
	pDev->m_VertexProcessing = vp;
	pDev->_RenderTargetCreate();			//����Ÿ��(�����) ���� : ����� 1���� ����� ���ϴ�.

											//�ܺο� ����..
	*ppDevice = pDev;

	return YN_OK;
}


/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 

/////////////////////////////////////////////////////////////////////////////// 
//
// B3YenaDevice9 : DX9 ���� ������ "����̽�" Ŭ���� 
//
//                DX �Ǵ� GL �� �������� �� ���ι����� ����(DX8, DX9, DX10, DX11 ��..) �ϰų�
//                �ػ�, ����Ÿ�� ���� �Ǵ� HWVP �Ǵ� SWVP �� �����ϴ� ���� ������ ���� ������ 
//                ó���ϴ� ���� �۾��� Ŭ����
//
/////////////////////////////////////////////////////////////////////////////// 

B3YenaDevice9::B3YenaDevice9(void)
{
	m_hWnd = NULL;
	ZeroMemory(&m_PresentParam, sizeof(m_PresentParam));

	m_hBmpRT = NULL;
	m_hSurfaceRT = NULL;
	m_BkColor = RGB(0, 0, 255);

	m_pVB = NULL;	//�� 
	m_FVF = 0;		//�� 
	m_Stride = 0;	//�� 

	m_PrimCnt = 0;	//��
	m_StartVtx = 0;	//��

}

B3YenaDevice9::~B3YenaDevice9(void)
{
	//Back-Buffer : Render Target ����.�� 
	_RenderTargetRelease();

	//���� ���� ��ü�� �����ϴ� ���� ����ڰ� å���� ���ϴ�.��
	//...SAFE_DELETE(m_pVB);	
}

///////////////////////////////////////////////////////////////////////////////
//
HDC  B3YenaDevice9::GetRT()
{
	return m_hSurfaceRT;
}

///////////////////////////////////////////////////////////////////////////////
//
COLORREF B3YenaDevice9::GetBkColor()
{
	return m_BkColor;
}


///////////////////////////////////////////////////////////////////////////////
//
//  ����ۿ� ����Ÿ���� ����.
//
int B3YenaDevice9::_RenderTargetCreate()
{
	HDC hdc = GetDC(m_hWnd);

	m_hSurfaceRT = CreateCompatibleDC(hdc);
	m_hBmpRT = (HBITMAP)CreateCompatibleBitmap(hdc, m_PresentParam.Width, m_PresentParam.Height);
	SelectObject(m_hSurfaceRT, m_hBmpRT);

	ReleaseDC(m_hWnd, hdc);

	return YN_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
// ����Ÿ�� ����.
//
void B3YenaDevice9::_RenderTargetRelease()
{
	DeleteObject(m_hBmpRT);
	DeleteDC(m_hSurfaceRT);
}

///////////////////////////////////////////////////////////////////////////////
//
// ��� �׸��� ����. : �������� �ʿ��� (����̽���) ���� �۾��� ����.
//
int B3YenaDevice9::BeginScene()
{
	//��Ʈ ���� �⺻�� 
	//SetBkColor(m_hSurfaceRT, m_BkColor);
	SetBkMode(m_hSurfaceRT, TRANSPARENT);

	return YN_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// ��� �׸��� ���� ; ������ ���ῡ �ʿ��� (����̽���) ���� �۾��� ����.
//
int B3YenaDevice9::EndScene()
{
	//...

	return YN_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// ����Ÿ�� Ŭ����.
//
// ���� : COLORREF col : RT �� ���� ������.
// ���� : 
//
int B3YenaDevice9::Clear(COLORREF col)
{
	HBRUSH hBrush = CreateSolidBrush(col);
	RECT rc = { 0, 0, m_PresentParam.Width,  m_PresentParam.Height };
	FillRect(m_hSurfaceRT, &rc, hBrush);
	DeleteObject(hBrush);

	m_BkColor = col;

	return YN_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// RT �� ����(�������� ���)�� Front Buffer �� ����մϴ�. "Flipping", "Swapping"
//
// ���� : ����
// ���� : ������ YN_OK �̿��� ��.
//
int B3YenaDevice9::Present()
{
	HDC hdc = GetDC(m_hWnd);
	BitBlt(hdc, 0, 0, m_PresentParam.Width, m_PresentParam.Height, m_hSurfaceRT, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);

	return YN_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// ����ڰ� ������ �ɼ����� �������۸� ����.
//
int B3YenaDevice9::CreateVertexBuffer(UINT Length,
							 		DWORD FVF,
									B3YENAPOOL Pool,
									LPB3YENAVERTEXBUFFER9* ppVB
									)		//��
{
	LPB3YENAVERTEXBUFFER9 pVB = new B3YenaVertexBuffer9;	//�������� ��ü ����.
	if (YN_INVALIED(pVB)) return YN_FAIL;

	if (YN_FAILED(pVB->Create(Length, FVF, Pool)))			//�������� Ȯ��.
	{
		//Error...
		return YN_FAIL;
	}


	//�ܺη� ����..
	*ppVB = pVB;


	return YN_OK;
}


///////////////////////////////////////////////////////////////////////////////
//
// ����� ���� �������۸� ����̽��� ���.
//
int B3YenaDevice9::SetVertexBuffer(
								LPB3YENAVERTEXBUFFER9 pVB,			//�������� ���� ������.
								UINT Stride							//�������� ������ 1����(����������) ũ��
								)		//��
{
	if (YN_INVALIED(pVB)) return YN_FAIL;

	m_pVB = pVB;
	m_Stride = Stride;

	return YN_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// ���� ���� �԰��� �����մϴ�. 
// SetStreamSource �� ��ϵ� �Ǵ� ����� �������ۿ� ������ �԰��� ����ؾ� �մϴ�.
//
int B3YenaDevice9::SetFVF(DWORD fvf)
{
	m_FVF = fvf;

	return YN_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// ���� ������ ������ 
//
// �� �޼ҵ��� ȣ�� ������ ��������, FVF, ���� ũ��(Stride) �� �������� �ʿ���
// ��� ������ ����̽��� ��ϵǾ� �־�� �մϴ�.
// 
int B3YenaDevice9::DrawPrimitive(
								B3YPRIMITIVETYPE PrimitiveType,	//������ ���� Ÿ��.
								UINT StartVertex,				//�������� ���� ���۹�ȣ (�������� ��)
								UINT PrimitiveCount				//�������� ���� ����.
								)		//��
{

	if (YN_INVALIED(m_pVB)) return YN_FAIL;
	if (YN_INVALIED(m_Stride)) return YN_FAIL;

	//������ ���� �ɼ� ����.
	m_PrimCnt = PrimitiveCount;
	m_StartVtx = StartVertex;

	//
	// �� ������ ���������κ��� ������ ������ �����մϴ�.
	//

	//1.���� ������ ����...
	_VertexPipeLine();

	//2.���� ������ ����...
	_GeometryPipeLine();

	//3.�ȼ� ������ ����...
	_PixelPipeLine();

	//4.���� ���...


	return YN_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// ���� ������ ���� ������ ���� : ��°���� GP ���� �Ѿ�ϴ�.
//
int B3YenaDevice9::_VertexPipeLine()		//��
{

	//�̹� ����� �̹� 2D ��ǥ�� ������ �����Ƿ�
	//�߰� ��ȯ�� �ʿ����, �ٷ� ȭ�鿡 ����մϴ�.
	//...


	return YN_OK;
}




///////////////////////////////////////////////////////////////////////////////
//
// ���� ������ ���� ������ ���� : ��°���� PP ���� �Ѿ�ϴ�.
//
int B3YenaDevice9::_GeometryPipeLine()		//��
{

	//�̹� ����� �̹� 2D ��ǥ�� ������ �����Ƿ�
	//�߰� ��ȯ�� �ʿ����, �ٷ� ȭ�鿡 ����մϴ�.
	//...

	return YN_OK;
}

int B3YenaDevice9::_PixelPipeLine()		//��
{

	//�̹� ����� �̹� 2D ��ǥ�� ������ �����Ƿ�
	//�߰� ��ȯ�� �ʿ����, �ٷ� ȭ�鿡 ����մϴ�.
	//
	UINT vtxCnt = m_pVB->m_SizeInByte / m_Stride;		//���� ���� Ȯ��.

	void* pOrgVB = m_pVB->_GetVBuffer();	//���� ����.

	BYTE* pCurrVB = (BYTE*)pOrgVB;			//���� ó������ �������� �ּ�. 
	BYTE* pCurrVtx = NULL;					//���� ó������ ������ �ּ�.
	UINT  faceCnt = 0;

	// ���� ����� Triangle-List �� ó���մϴ�.��
	// Triangle-List �� Face ���� 3���� ������ ����մϴ�.  
	//
	//for(int i=0; i<vtxCnt; i+=3)				//3���� ó��..(���� �� �׸���..)
	for (UINT i = m_StartVtx; i<vtxCnt; i += 3)		//���� ��������, �׸���.��
	{
		//���� ���ϵ�����(�ﰢ��) ������ ���...
		pCurrVB = (BYTE*)pOrgVB + (i)*m_Stride;

		//ù��° ���� 
		pCurrVtx = pCurrVB;
		B3YVECTOR2  v0 = *(B3YVECTOR2*)pCurrVtx;		//��ǥ ���.


														//2��° ����..
		pCurrVtx = pCurrVB + m_Stride;					//1�� ũ�⸸ŭ �̵�. 
		B3YVECTOR2  v1 = *(B3YVECTOR2*)pCurrVtx;		//��ǥ ���.


														//3��° ����..
		pCurrVtx = pCurrVB + (2)*m_Stride;				//1�� ũ�⸸ŭ �̵�. 
		B3YVECTOR2  v2 = *(B3YVECTOR2*)pCurrVtx;		//��ǥ ���.


														//���� 3�� �׸���.
														//.. 	
														//v0->v1
		_DrawLine(v0, v1);

		//v0->v2
		_DrawLine(v0, v2);

		//v1->v2
		_DrawLine(v1, v2);


		//���� ���� �̻��� �ﰢ���� �׷�����, �۾� ����...�� 
		if (++faceCnt >= m_PrimCnt)
			break;
	}



	return YN_OK;
}

/*
///////////////////////////////////////////////////////////////////////////////
//
// ���� �׸���. (ver.User)
//
int B3YenaDevice9::_DrawLine(B3YVECTOR2& v0, B3YVECTOR2& v1)
{

//�޼ҵ� ����...(����) ����

return YN_OK;
}
*/



///////////////////////////////////////////////////////////////////////////////
//
// ���� �׸���. (ver.GDI)
//
int B3YenaDevice9::_DrawLine(B3YVECTOR2& v0, B3YVECTOR2& v1)
{
	MoveToEx(m_hSurfaceRT, (int)v0.x, (int)v0.y, NULL);
	LineTo(m_hSurfaceRT, (int)v1.x, (int)v1.y);

	return YN_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// ������ ���� �ɼ� ���� : 
//
int B3YenaDevice9::SetRenderState(DWORD state, DWORD value)		//��
{
	//...
	return YN_OK;
}


///////////////////////////////////////////////////////////////////////////////
//
//




/**************** end of "B3Yena.h" ***********************************/
