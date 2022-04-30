#pragma once

typedef	struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

}INFO;

struct Vector2D
{
	float x;
	float y;
};

typedef struct tagLinePoint
{
	float fX;
	float fY;
	
	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }

	tagLinePoint(float fA, float fB)
		:fX(fA),fY(fB) {  }

}LINEPOINT;

typedef struct tagLineInfo
{
	LINEPOINT tLPoint;
	LINEPOINT tRPoint;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOINT& _tLPoint, LINEPOINT& _tRPoint)
		:tLPoint(_tLPoint), tRPoint(_tRPoint) { }

}LINE;

typedef struct statInfo
{
	int                     m_Max_Life;//�ִ� ���
	int                     m_Life;//���� ���
	bool                    m_Hammer;//�ظ� ������ ���� Ȯ��
}STAT;
