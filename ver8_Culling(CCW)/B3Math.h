// B3Math.H : �������

#pragma once

//OpenGL ǥ�� �������. �ʼ����
//#include <GL/gl.h>
//#include <GL/glu.h>

// Radian or Degree �ٲٱ� ��ũ��
#define YN_PI   3.141592f
#define YNToRadian(a)  (a/180.0f * YN_PI)
#define YNToAngle(r)   (r * 180.0f / YN_PI)
#define YNToDegree(r)  YNToAngle(r)

// ���� ������.
//
// ��������͸� '����:��'���� ����������,
// ����/��� ����ÿ��� '����:��'���� ó������ ����սô�.
// �Ʒ��� ���� ǥ���� ����.
//
//  x   or   x
//  y        y
//  z        z
//           w
//

// 2���� ���� ����ü.
//
struct B3YVECTOR2 {
	float x, y;
};


// 3���� ���� ����ü.
//
struct B3YVECTOR3 {
	float x, y, z;
};


// 4���� ����.����ü.
//
struct B3YVECTOR4 {
	float x, y, z, w;
};



// VECTOR2  �Ϲ� ����ü + ������/������ �����ε�.
//
class B3YXVECTOR2
{
public:
	float x, y;
public:
	B3YXVECTOR2() { x = 0;  y = 0; }
	B3YXVECTOR2(float _x, float _y) { x = _x;  y = _y; }
	B3YXVECTOR2(B3YVECTOR2 v) { x = v.x;  y = v.y; }

	//������ �����ε�.��
	B3YXVECTOR2 operator + (B3YXVECTOR2 rhs);
	B3YXVECTOR2 operator - (B3YXVECTOR2 rhs);
	B3YVECTOR2 operator = (B3YXVECTOR2 rhs);
	operator B3YVECTOR2* ();
};
typedef B3YXVECTOR2 VECTOR2;

// 2���� ���� : ������ ����� �����, 'CCW'.Back - Face Culling �� ����
//
float B3YXVec2CCW(B3YXVECTOR2* v0, B3YXVECTOR2* v1);	//��

// VECTOR3  �Ϲ� ����ü + ������/������ �����ε�.
//
class B3YXVECTOR3
{
public:
	float x, y, z;
public:
	B3YXVECTOR3(float _x, float _y, float _z) { x = _x;  y = _y;   z = _z; }
	B3YXVECTOR3(B3YVECTOR3 v) { x = v.x;  y = v.y;  z = v.z; }
};
typedef B3YXVECTOR3 VECTOR3;



// VECTOR4 �Ϲ� ����ü + ������/������ �����ε�.
//
class B3YXVECTOR4
{
public:
	float x, y, z, w;
public:
	B3YXVECTOR4(float _x, float _y, float _z, float _w) { x = _x;  y = _y;   z = _z;  w = _w; }
	B3YXVECTOR4(B3YVECTOR4 v) { x = v.x;  y = v.y;  z = v.z; w = v.w; }

};
typedef B3YXVECTOR4 VECTOR4;




//�÷� ����ü.
struct B3YCOLOR4 {
	float r, g, b, a;
};
typedef B3YCOLOR4 COLOR;

#define TOCOLOR(col)  (*(COLOR*)&(col))
COLOR   B3YXColor(float r, float g, float b, float a);




/************* end of file "B3Math.h" *******************************************/





