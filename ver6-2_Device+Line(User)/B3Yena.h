//
// B3Yena.h : DX �⺻ ��� ����.

#pragma once

#include "Define.h"
#include "B3Math.h"

/////////////////////////////////////////////////////////////////////////////// 
//
// ����Ÿ�� (�����) - ���� ���� ����ü : D3DPRESENT_PARAMETERS ����
//
struct YENAPRESENT_PARAMETERS {

	DWORD Width;			//�ػ� : Ŭ���̾�Ʈ ��������.
	DWORD Height;
	DWORD BackBuffercnt;	//����� ����
	BOOL  Windowed;			//â��� ����?

};

/////////////////////////////////////////////////////////////////////////////// 
//
//  �ػ� ���� ����ü. : D3DDISPLAYMODE ����
//
struct YENADISPLAYMODE {
	DWORD Width, Height;
};

/////////////////////////////////////////////////////////////////////////////// 
//
// ���� ó�� - ����ȭ ����.  : D3DCREATE ����
//
enum BEHAVIOR_FLAG
{
	YENACREATE_SOFTWARE_VERTEXPROCESSING,	//CPU �� ���� ������ ó��. 
	YENACREATE_HARDWARE_VERTEXPROCESSING,	//GPU �� ���� ������ ó��.
	//YENACREATE_MIXED_VERTEXPROCESSING		//CPU / GPU ȥ�� ���� ����.
	//YENACREATE_MULTITHREADED				//���߾����� ȯ�� ȣȯ�� �߰�.
	//...
};

// �޸� ���� ���� �ɼ�.��
enum B3YENAPOOL {
	B3YPOOL_DEFAULT = 1,	//�⺻�� : ���� �޸� ���. 
	B3YPOOL_MANAGED,		//�ڵ����� : ���� - �ý��� ȥ��.
	B3YPOOL_SYSTEM,			//�ý��۸޸� ���. (����� �� �ɼǸ� ��ȿ) ��

};

// ���ϵ��� Ÿ��.��
//
enum B3YPRIMITIVETYPE
{
	B3YPT_POINTLIST = 1,
	B3YPT_LINELIST,
	B3YPT_LINESTRIP,
	B3YPT_TRIANGLELIST,
	B3YPT_TRIANGLESTRIP,
	B3YPT_TRIANGLEFAN,

};

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

// ���� �԰� ���� (�ټ��� ���� �����Ͽ� ����/����մϴ�) : D3DFVF ���� ��
// 
#define  B3YFVF_XY			 0x0001		//2D ��ǥ.(DX ���� �������� ����.Yena ����)��
//#define  B3YFVF_XYZ		 0x0002		//3D ��ǥ.(�� ��ȯ)(Local)
//#define  B3YFVF_XYZRHW	 0x0004		//3D ��ǥ.(��ȯ �Ϸ�) XY + Depth
//#define  B3YFVF_NORMAL	 0x0010		//���. 
#define  B3YFVF_DIFFUSE		 0x0040		//Ȯ���(Diffuse) ����
//#define  B3YFVF_SPECULAR	 0x0080		//���ݻ�(Specular) ����. 
//#define  B3YFVF_TEX1		 0x0100		//�ؽ�ó ��ǥ.1 
//#define  B3YFVF_TEX2		 0x0200		//�ؽ�ó ��ǥ.2 



#define CHECK( value, bit) (((value) & (bit)) == bit)



//��Ÿ Ŭ�������� B3YenaDevice  �� �ν��ϵ��� �̸� ������.
class B3YenaDevice9;
typedef B3YenaDevice9  B3YENADEVICE9;		//DX9 ����.
typedef B3YenaDevice9* LPB3YENADEVICE9;		//DX9 ����.

#define YENA_VERSION  9		//DX9.0


/////////////////////////////////////////////////////////////////////////////// 
//
// B3YenaVertexBuffer : ���� ����.���� Ŭ���� : IDirect3DVertexBuffer9 ���� �� 
//                    : DX �޼ҵ�� (����)������ �ñ״���(Signature) �� 
//                      �����ϴ� ���� ��ǥ�Դϴ�.
// 
/////////////////////////////////////////////////////////////////////////////// 

#pragma region C++ friend ����
/*
friend �� ���� �����ڸ� �Ϻ��� ������ �� �ִ� ������ ���
private �� protected �� friend�� ����� ��󿡰Դ� �Ϻ��ϰ� public���� �ۿ�.
��ü ���� ������ ���� ���� ���信 �������� �����
friend class : Ư�� Ŭ���� ���忡�� �ٸ� Ŭ������ ģ���� �����ϴ°� publicó�� �ν�
friend ��� �Լ� : Ŭ���� ��ü�� �ƴ� Ŭ������ Ư�� ��� �Լ����� ������� ����
friend ���� �Լ� : private , proteced ���� �����ڸ� �����ϰ� Ŭ���� ������ ����� ���ٰ���
*/
#pragma endregion

class B3YenaVertexBuffer9		//��
{
	friend class B3YenaDevice9;
protected:
	void* m_pVBuffer;		//�������� : ���� �����Ͱ� �����.

	DWORD m_SizeInByte;		//�������� ũ�� (����Ʈ)
	DWORD m_FVF;			//�������� �԰� ���� �÷���.
	UINT  m_Stride;			//�������� ���� 1����(���� ���� �ϳ�) �� ũ��.


protected:
	B3YenaVertexBuffer9(void);			//��ü���� ������, ������ ����. 

	void* _GetVBuffer() { return m_pVBuffer; }
public:
	virtual ~B3YenaVertexBuffer9(void);


	//�������� ���� : (DX) �־��� �ɼǿ� ���߾� VRAM  �� Ȯ���մϴ�.
	//
	int Create(UINT Length,		//'���� ����'�� ��ü ũ�� (����Ʈ)	
		DWORD FVF,				//'����' �԰�.  
		B3YENAPOOL Pool			//�޸� ��� �ɼ�.  
	);		//��

	//�������� �ּ� ��� : ���� DX �� �װͰ��� ��Ȱ�� �ٸ�����, 
	//������ ����� �����մϴ�.��
	int Lock(UINT OffsetToLock,		//[in]������ ���� ������ �ɼ� �ּ�. �⺻�� 0. 
		void** ppbData				//[out]���Ϲ��� ������.
	);

	//���� ���� �ݱ�. (Ư���� �ϴ� ���� ����)
	void Unlock() { }



};

typedef B3YenaVertexBuffer9* LPB3YENAVERTEXBUFFER9;


/////////////////////////////////////////////////////////////////////////////// 
//
// B3Yena SW Renderer : ���� ������ '����̽� Device' ���� ������ �ֻ��� Ŭ����
//					  : Direct3D ����
//                    : DX �޼ҵ�� (����)������ �ñ״���(Signature) �� 
//                      �����ϴ� ���� ��ǥ�Դϴ�.
//
/////////////////////////////////////////////////////////////////////////////// 




class B3Yena							
{
	friend B3Yena* B3YenaCreate9(DWORD ver);
	//friend class B3YenaDevice9;			 


protected:
	B3Yena(void);			//��ü���� ������, ������ ����. 
public:
	virtual ~B3Yena(void);


	// �ܺ� ���� �޼ҵ�� : DX �޼ҵ�� (����)������ �ñ״���(Signature) �� 
	//                        �����ϴ� ���� ��ǥ�Դϴ�. 
	//
	int CreateDevice(HWND hwnd,			//[in]����̽��� ������ ��ǥ ������ �ڵ�.
		YENAPRESENT_PARAMETERS* pp,		//[in]����̽� ȭ�� ���� ����.	
		DWORD vp,						//[in]�������� ��� ���� (����� SW �� ����)
		LPB3YENADEVICE9* pDev			//[out]������ ���Ϲ��� ����̽� ��ü ������.
	);

};
typedef B3Yena* LPB3YENA;


// B3Yena9 ��ü ���� �Լ�
B3Yena* B3YenaCreate9(DWORD ver);


/////////////////////////////////////////////////////////////////////////////// 
//
// B3YenaDevice9 : DX9 ���� ������ "����̽�" Ŭ����, 
//                 IDirect3DDevice9 ���� 
//                 
//                DX �Ǵ� GL �� �������� �� ���ι����� ����(DX8, DX9, DX10, DX11 ��..) �ϰų�
//                �ػ�, ����Ÿ�� ���� �Ǵ� HWVP �Ǵ� SWVP �� �����ϴ� ���� ������ ���� ������ 
//                ó���ϴ� ���� �۾��� Ŭ����
//
//               : DX �޼ҵ�� (����)������ �ñ״���(Signature) �� 
//                �����ϴ� ���� ��ǥ�Դϴ�.
//
/////////////////////////////////////////////////////////////////////////////// 

class B3YenaDevice9				
{
	friend class B3Yena;

protected:

	// ��� ȭ�� ���� ����.
	HWND		 m_hWnd;
	YENAPRESENT_PARAMETERS m_PresentParam;
	DWORD		 m_VertexProcessing;
	//YENADISPLAYMODE  m_Display; 


	// ����Ÿ��(Back-Buffer) ������ �ڵ�.
	//
	HBITMAP  m_hBmpRT;				
	HDC		 m_hSurfaceRT;			
	COLORREF m_BkColor;

	//���� ���� (�̹��� �������� ..) ��
	//DrawPrimitive �� ���.
	LPB3YENAVERTEXBUFFER9 m_pVB;		// �������� ��ϵ� ���� ����.
	DWORD m_FVF;						// �������� ��ϵ� ���� �԰�
	UINT  m_Stride;						// �������� ��ϵ� ���� 1������ ũ��

	//�׸��� �ɼ�.(DrawPrimitive ȣ��� �Էµ�)��
	UINT m_PrimCnt;		//�̹��� �׷��� Face ����.
	UINT m_StartVtx;	//�̹��� �׷��� (����) ���� ��ȣ.

protected:

	// ���� �޼ҵ��. '���� _ '�� ���ξ�� ǥ���մϴ�.
	//
	int  _RenderTargetCreate();
	void _RenderTargetRelease();

	// ������ ������ ���κ� ���� �޼ҵ�.��
	//
	int _VertexPipeLine();		//���� ������ ����.
	int _GeometryPipeLine();	//���� ������ ����.	
	int _PixelPipeLine();		//�ȼ� ������ ����.	

	//�׸��� �Լ�.��
	int _DrawLine(B3YVECTOR2& start, B3YVECTOR2& end);

protected:
	B3YenaDevice9(void);			//��ü���� ������, ������ ����. 
public:
	virtual ~B3YenaDevice9(void);

	// ��������� ������ Accessors
	HDC		 GetRT();
	COLORREF GetBkColor();

	// �ܺ� ���� �޼ҵ�� : DX �޼ҵ�� (����)������ �ñ״���(Signature) �� 
	//                        �����ϴ� ���� ��ǥ�Դϴ�. 
	// 
	int BeginScene();
	int EndScene();
	int Clear(COLORREF col);
	int Present();

	// ������ ���� �޼ҵ��.
	//

	// ���� ���� ����.��
	int CreateVertexBuffer(
		UINT Length,					//[in]'���� ����'�� ��ü ũ�� (����Ʈ)	
		DWORD FVF,						//[in]'����' �԰�.
		B3YENAPOOL Pool,				//[in]�ý��۸޸� ���. (����� �� �ɼǸ� ��ȿ) 
		LPB3YENAVERTEXBUFFER9* ppVB		//[out] ������ ���ϵǴ� ���� �����ͤ�
	);

	// ����̽��� ���� ���� ���.��
	int SetVertexBuffer(
		LPB3YENAVERTEXBUFFER9 pVB,			//�������� ���� ������. 
		UINT Stride							//�������� ������ 1����(����������) ũ��
	);

	// ���� ������ �԰� ���.��
	int SetFVF(DWORD FVF);									//���� �԰� : '�̹��� �������� ���������� �װͰ� �����ؾ� ��.

															// ������..(������ ��ϵ� ���� ���۸� ���)
	int DrawPrimitive(B3YPRIMITIVETYPE PrimitiveType,		//������ ���� Ÿ��.
		UINT StartVertex,					//�������� ���������� ���� ���� �ε���.(�������� ��)
		UINT PrimitiveCount					//�������� ���ϵ��� ����.
	);

	// ������ ���� ��ȭ ����.��
	int SetRenderState(DWORD state, DWORD value);
	//int SetTransform(DWORD, MATRIX*);
};
//typedef B3YenaDevice9* LPB3YENADEVICE9;		//DX9 ����.

#define SetStreamSource  SetVertexBuffer

/////////////////////////////////////////////////////////////////////////////// 
//
// ��Ÿ ����̽� ���� Ŭ������ Ȯ�� ���� ���ô� �Ʒ��� �����ϴ�.
// Ȯ�强�� ����� Ŭ���� ���躣�̽� �Դϴٸ�, �̹� ������Ʈ������ 
// ����/������� �ʽ��ϴ�.  "�̷������� �� �� �ְڱ�.." ������ ���� �ֽʽÿ�
//

/////////////////////////////////////////////////////////////////////////////// 
//
// B3YenaDevice10 : DX10 ���� ������ "����̽�" Ŭ���� 
//                : ID3D10Device ���� 
//
/////////////////////////////////////////////////////////////////////////////// 

class B3YenaDevice10
{
protected:

	//...DX10 ���� Device ...
};

/////////////////////////////////////////////////////////////////////////////// 
//
// B3YenaDevice11 : DX11 ���� ������ "����̽�" Ŭ���� 
//                : ID3D11Device ���� 
//
//
/////////////////////////////////////////////////////////////////////////////// 


class B3YenaDevice11
{
protected:

	//...DX11 ���� Device ...
};

/////////////////////////////////////////////////////////////////////////////// 
//
// B3YenaDeviceGL : OpenGL ���� ������ "����̽�" Ŭ���� 
//
//
/////////////////////////////////////////////////////////////////////////////// 


class B3YenaDeviceGL
{
protected:

	//...OpenGL ���� Device ...
};





/**************** end of "B3Yena.h" ***********************************/
