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

typedef struct statInfo
{
	int                     m_Max_Life;//�ִ� ���
	int                     m_Life;//���� ���
	bool                    m_Hammer;//�ظ� ������ ���� Ȯ��
}STAT;