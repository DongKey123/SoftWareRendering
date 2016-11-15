//Define.h : �⺻ ���� ����

#pragma once


#include "windows.h"
#pragma warning(disable 4305)
/////////////////////////////////////////////////////////////////////////////
//
#ifdef YES_
#undef YES_
#endif
#define YES_ 1
#define NO_	 0

/////////////////////////////////////////////////////////////////////////////
//
#include "assert.h"
#define ASSERT(Val) assert((Val))

#define YN_INVALIED(res) ((res) == NULL)
#define YN_VALIED(res) ((res) != NULL)
#define YN_FAILED(res) ((res) < 0 )

#define YN_OK       0 
#define YN_FALSE   -1 
#define YN_FAIL    YN_FALSE
#pragma region assert ����
/*
assert()��ũ�δ� ǥ���� �����Ͽ� ���α׷��� ������ ���� Ȯ���ϸ� ������ ��� ���� �޽����� ���
*/
#pragma endregion 

/////////////////////////////////////////////////////////////////////////////
//
#define _LOGFILE_ON_			//�α� ���� �����ϱ�..

///////////////////////////////////////////////////////////////////////////////////////
//
// DXUtil.h �� ���� �����. 2004.06.07. 
//

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(pBuff) if((pBuff)){ (pBuff)->Release(); (pBuff) = NULL; }
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(pBuff)	if((pBuff)){ delete (pBuff); (pBuff) = NULL; }
#endif
#ifdef SAFE_DELETE_ARRAY
#define SAFE_DELARRY  SAFE_DELETE_ARRAY
#else
#define SAFE_DELARRY(pBuff) if((pBuff)){ delete [] (pBuff); (pBuff) = NULL; }
#endif

/////////////////////////////////////////////////////////////////////////////
//
//'��'->'����' ���� ���� ��ũ��.
// pi : 180 = r : 1 
// r = pi / 180      ��  1 ���� : 0.017444444444444444
// 
#define B3Y_PI  3.141592f 
#define MAKERADIAN(do) ( (float)(B3Y_PI/180.0f)*((float)do) )

/*********** end of file "B3D_Define.h" *******************************/