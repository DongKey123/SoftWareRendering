//
// B3Yena.h : DX �⺻ ��� ����.

#pragma once

#include "Define.h"

/////////////////////////////////////////////////////////////////////////////// 
//
// ����Ÿ�� (�����) - ���� ���� ����ü : D3DPRESENT_PARAMETERS ���� ��
//
struct YENAPRESENT_PARAMETERS {

	DWORD Width;			//�ػ� : Ŭ���̾�Ʈ ��������.
	DWORD Height;
	DWORD BackBuffercnt;	//����� ����
	BOOL  Windowed;			//â��� ����?

};

/////////////////////////////////////////////////////////////////////////////// 
//
//  �ػ� ���� ����ü. : D3DDISPLAYMODE ���� ��
//
struct YENADISPLAYMODE {
	DWORD Width, Height;
};

/////////////////////////////////////////////////////////////////////////////// 
//
// ���� ó�� - ����ȭ ����.  : D3DCREATE ���� ��
//
enum BEHAVIOR_FLAG
{
	YENACREATE_SOFTWARE_VERTEXPROCESSING,	//CPU �� ���� ������ ó��. 
	YENACREATE_HARDWARE_VERTEXPROCESSING,	//GPU �� ���� ������ ó��.
	//YENACREATE_MIXED_VERTEXPROCESSING		//CPU / GPU ȥ�� ���� ����.
	//YENACREATE_MULTITHREADED				//���߾����� ȯ�� ȣȯ�� �߰�.
	//...
};

/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////// 

//��Ÿ Ŭ�������� B3YenaDevice  �� �ν��ϵ��� �̸� ������.�� 
class B3YenaDevice9;
typedef B3YenaDevice9  B3YENADEVICE9;		//DX9 ����.
typedef B3YenaDevice9* LPB3YENADEVICE9;		//DX9 ����.

#define YENA_VERSION  9		//DX9.0


/////////////////////////////////////////////////////////////////////////////// 
//
// B3Yena SW Renderer : ���� ������ '����̽� Device' ���� ������ �ֻ��� Ŭ����
//					  : Direct3D ���� ��
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


class B3Yena							//��
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
	int CreateDevice(HWND hwnd,						//[in]����̽��� ������ ��ǥ ������ �ڵ�.
		YENAPRESENT_PARAMETERS* pp,	//[in]����̽� ȭ�� ���� ����.	
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
//                 IDirect3DDevice9 ���� ��
//                 
//                DX �Ǵ� GL �� �������� �� ���ι����� ����(DX8, DX9, DX10, DX11 ��..) �ϰų�
//                �ػ�, ����Ÿ�� ���� �Ǵ� HWVP �Ǵ� SWVP �� �����ϴ� ���� ������ ���� ������ 
//                ó���ϴ� ���� �۾��� Ŭ����
//
//               : DX �޼ҵ�� (����)������ �ñ״���(Signature) �� 
//                �����ϴ� ���� ��ǥ�Դϴ�.
//
/////////////////////////////////////////////////////////////////////////////// 

class B3YenaDevice9				//��
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
	HBITMAP  m_hBmpRT;				//��
	HDC		 m_hSurfaceRT;			//��
	COLORREF m_BkColor;




protected:

	// ���� �޼ҵ��. '���� _ '�� ���ξ�� ǥ���մϴ�.
	//
	int  _RenderTargetCreate();
	void _RenderTargetRelease();


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


	//int SetRenderState(DWORD, DWORD); 
	//int SetTransform(DWORD, MATRIX*);
	//int DrawPrimitive(); 
};


/////////////////////////////////////////////////////////////////////////////// 
//
// ��Ÿ ����̽� ���� Ŭ������ Ȯ�� ���� ���ô� �Ʒ��� �����ϴ�.
// Ȯ�强�� ����� Ŭ���� ���躣�̽� �Դϴٸ�, �̹� ������Ʈ������ 
// ����/������� �ʽ��ϴ�.  "�̷������� �� �� �ְڱ�.." ������ ���� �ֽʽÿ�
//

/////////////////////////////////////////////////////////////////////////////// 
//
// B3YenaDevice10 : DX10 ���� ������ "����̽�" Ŭ���� 
//                : ID3D10Device ���� ��
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
//                : ID3D11Device ���� ��
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
