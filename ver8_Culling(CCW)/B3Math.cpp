#include "Windows.h"  
#include "stdio.h"
#include "stdlib.h" 
#include "math.h"

#include "B3Math.h"

///////////////////////////////////////////////////////////////////////////////
//
// VECTOR2
//
///////////////////////////////////////////////////////////////////////////////

B3YXVECTOR2 B3YXVECTOR2::operator + (B3YXVECTOR2 rhs)
{
	B3YXVECTOR2 v;
	v.x = x + rhs.x;
	v.y = y + rhs.y;

	return v;
}

B3YXVECTOR2 B3YXVECTOR2::operator - (B3YXVECTOR2 rhs)
{
	B3YXVECTOR2 v;
	v.x = x - rhs.x;
	v.y = y - rhs.y;

	return v;
}

B3YXVECTOR2::operator B3YVECTOR2*()
{
	return (B3YVECTOR2*)this;
}

///////////////////////////////////////////////////////////////////////////////
//
// 2���� ���� : ������ ����� �����, 'CCW' .Back-Face Culling �� ����
//  
// 2�������δ� ���������� ������ �Ұ����ϹǷ� 3�������� Ȯ����. �Ʒ��� ��������.
// v0=(x1,y1,0) cross  v1=(x2,y2,0). 
// �Ǵ� �Ʒ� ���� ����.
/* [3���� ���� ����]
VECTOR3 v;
v.x = v0.y * v1.z - v0.z * v1.y;
v.y = v0.z * v1.x - v0.x * v1.z;
v.z = v0.x * v1.y - v0.y * v1.x;  <-- z ���������ε� ���� ����
									[2D Screen ���� ����] z<=0 �̸�, "�޸�", z>0 �̸� "�ո�"
									[3D ����(DX, ViewSpace) ����]  z<=0 �̸� "�ո�", z>0 �̸� "�޸�"
*/

float B3YXVec2CCW(B3YXVECTOR2* v0, B3YXVECTOR2* v1)	//��
{
	float z = v0->x * v1->y - v0->y * v1->x;
	return z;
}

/************* end of file "Math.cpp" *******************************************/
