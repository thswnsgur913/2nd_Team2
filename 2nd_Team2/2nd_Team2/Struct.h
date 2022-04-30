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
	int                     m_Max_Life;//최대 목숨
	int                     m_Life;//현재 목숨
	bool                    m_Hammer;//해머 아이템 소유 확인
}STAT;