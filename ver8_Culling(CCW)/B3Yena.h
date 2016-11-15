//
// B3Yena.h : DX �⺻ ��� ����.

#pragma once

#include "Define.h"
#include "B3Math.h"


#pragma region CW�� CCW�� ������
/*
�׸��� ���⿡ ���� CW �� CCW�� ���� -> ���ӳ����� �ո�� �޸��� ������ ������ ��
CW(ClockWise) : �ð����
CCW(CounterClockWise) : �ݽð����
// ������ �����Ҷ� (�ؿ��� �����Ҷ� res �� �ݴ�)
res = (A.x * B.y + B.x * C.y + C.x * A.y) - (A.x * C.y + B.x * A.y + C.x * B.y)
res == 0 : �� C�� ���� AB�� �������� �ֽ��ϴ�. (�� �� ��� �������� �ֽ��ϴ�.)
res < 0  : �� C�� ���� AB�� �ݽð���⿡ �ֽ��ϴ�.
res > 0  : �� C�� ���� AB�� �ð���⿡ �ֽ��ϴ�.
*/
#pragma endregion
inline int IsCW(int x1, int y1, int x2, int y2, int x3, int y3) {
	int temp = x1*y2 + x2*y3 + x3*y1;
	temp = temp - y1*x2 - y2*x3 - y3*x1;
	if (temp > 0) {
		return 1;
	}
	else if (temp < 0) {
		return -1;
	}
	else {
		return 0;
	}
}

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

// �޸� ���� ���� �ɼ�.
enum B3YENAPOOL {
	B3YPOOL_DEFAULT = 1,	//�⺻�� : ���� �޸� ���. 
	B3YPOOL_MANAGED,		//�ڵ����� : ���� - �ý��� ȥ��. , ����̽��ν�Ʈ �ڵ������� �ذ��ϱ�����
	B3YPOOL_SYSTEM,			//�ý��۸޸� ���. (����� �� �ɼǸ� ��ȿ) 

};

// ���ϵ��� Ÿ��.
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
// 
// ������ ���� �ɼ�. : D3DRENDERSTATETYPE ����. ��
//
typedef enum _B3YRENDERSTATETYPE {
	//B3YRS_ZENABLE                   = 7,    
	B3YRS_FILLMODE					= 8,	  //Fill Mode State.
	//B3YRS_ZWRITEENABLE              = 14,   // TRUE to enable z writes 
	//B3YRS_ALPHATESTENABLE           = 15,   // TRUE to enable alpha tests 
	B3YRS_CULLMODE                  = 22,	  // Culling State 
	//B3YRS_ALPHABLENDENABLE          = 27,   // TRUE to enable alpha blending 
	//B3YRS_FOGENABLE                 = 28,   // TRUE to enable fog blending  
	//B3YRS_SPECULARENABLE            = 29,   // TRUE to enable specular  
	//B3YRS_LIGHTING                  = 137,
	//B3YRS_AMBIENT                   = 139, 

	//������ ���°��� ��� �߰��� ����.
	//..

	B3YRS_MAX_

} B3YRENDERSTATETYPE;

//
// Fill Mode �� �ɼ�. : D3DFILLMODE  ����. ��
//
typedef enum _B3YFILLMODE {
	B3YFILL_POINT			= 1,		//������ �׸���.
	B3YFILL_WIREFRAME		= 2,		//������ �׸���.
	B3YFILL_SOLID			= 3,		//(����)������ ä���.
} B3YFILLMODE;

//
// Culling Mode �� �ɼ�.: D3DCULL ���� �� 
//
typedef enum _B3YCULL {
	B3YCULL_NONE = 1,	//�ø� ����. 
	B3YCULL_CW = 2,		//�ð���� �ø�.
	B3YCULL_CCW = 3,	//�ݽð���� �ø�.(�⺻��) ��
						//B3YCULL_FORCE_DWORD         = 0x7fffffff, /* force 32-bit size enum */
} B3YCULL;

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

// ���� �԰� ���� (�ټ��� ���� �����Ͽ� ����/����մϴ�) : D3DFVF ���� 
// 
#define  B3YFVF_XY			 0x0001		//2D ��ǥ.(DX ���� �������� ����.Yena ����)
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
// B3YenaVertexBuffer : ���� ����.���� Ŭ���� : IDirect3DVertexBuffer9 ���� 
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

class B3YenaVertexBuffer9		
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
	);		

	//�������� �ּ� ��� : ���� DX �� �װͰ��� ��Ȱ�� �ٸ�����, 
	//������ ����� �����մϴ�
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

	// ������ ���°�
	//
	DWORD  m_RState[B3YRS_MAX_];

	// ����Ÿ��(Back-Buffer) ������ �ڵ�.
	//
	HBITMAP  m_hBmpRT;				
	HDC		 m_hSurfaceRT;			
	COLORREF m_BkColor;

	//���� ���� (�̹��� �������� ..) 
	//DrawPrimitive �� ���.
	LPB3YENAVERTEXBUFFER9 m_pVB;		// �������� ��ϵ� ���� ����.
	DWORD m_FVF;						// �������� ��ϵ� ���� �԰�
	UINT  m_Stride;						// �������� ��ϵ� ���� 1������ ũ��
	UINT  m_FaceNum;					// ���̽� ����

	//�׸��� �ɼ�.(DrawPrimitive ȣ��� �Էµ�)
	UINT m_PrimCnt;		//�̹��� �׷��� Face ����.
	UINT m_StartVtx;	//�̹��� �׷��� (����) ���� ��ȣ.

protected:

	// ���� �޼ҵ��. '���� _ '�� ���ξ�� ǥ���մϴ�.
	//
	int  _RenderTargetCreate();
	void _RenderTargetRelease();

	// ������ ���� �ʱ�ȭ..
	void _InitRenderState();		
	bool _FaceCulling(B3YXVECTOR2 v0, B3YXVECTOR2 v1, B3YXVECTOR2 v2);		//���̽� �ø�. false ���Ͻ�, �׸��� ���� ����.��

	// ������ ������ ���κ� ���� �޼ҵ�.
	//
	int _VertexPipeLine();		//���� ������ ����.
	int _GeometryPipeLine();	//���� ������ ����.	
	int _PixelPipeLine();		//�ȼ� ������ ����.	

	

	//�׸��� �Լ�.
	int _DrawLine(B3YVECTOR2& start, B3YVECTOR2& end);
	int _DrawFace(B3YVECTOR2& v0, B3YVECTOR2& v1, B3YVECTOR2& v2);
	int _SortVert3(B3YVECTOR2& high, B3YVECTOR2& middle, B3YVECTOR2& bottom,//out
		B3YVECTOR2& v0, B3YVECTOR2& v1, B3YVECTOR2& v2);//in

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

	// ���� ���� ����
	int CreateVertexBuffer(
		UINT Length,					//[in]'���� ����'�� ��ü ũ�� (����Ʈ)	
		DWORD FVF,						//[in]'����' �԰�.
		B3YENAPOOL Pool,				//[in]�ý��۸޸� ���. (����� �� �ɼǸ� ��ȿ) 
		LPB3YENAVERTEXBUFFER9* ppVB		//[out] ������ ���ϵǴ� ���� �����ͤ�
	);

	// ����̽��� ���� ���� ���
	int SetVertexBuffer(
		LPB3YENAVERTEXBUFFER9 pVB,			//�������� ���� ������. 
		UINT Stride							//�������� ������ 1����(����������) ũ��
	);

	// ���� ������ �԰� ���
	int SetFVF(DWORD FVF);									//���� �԰� : '�̹��� �������� ���������� �װͰ� �����ؾ� ��.

															// ������..(������ ��ϵ� ���� ���۸� ���)
	int DrawPrimitive(B3YPRIMITIVETYPE PrimitiveType,		//������ ���� Ÿ��.
		UINT StartVertex,					//�������� ���������� ���� ���� �ε���.(�������� ��)
		UINT PrimitiveCount					//�������� ���ϵ��� ����.
	);

	// ������ ���� ��ȭ ����.
	int SetRenderState(B3YRENDERSTATETYPE state, DWORD value);		//���� ����.
	void GetRenderState(B3YRENDERSTATETYPE state, DWORD* value);	//���� ���� ���.

	// ������ ���� ��ȭ ����
	//int SetRenderState(DWORD state, DWORD value);
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
