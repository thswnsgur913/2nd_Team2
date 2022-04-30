#pragma once
#include "Line.h"
#include "Include.h"

class CLinePlat
{
public:
	CLinePlat();
	~CLinePlat();

	void Initialize(void);
	void Render(HDC hDC);
	void Release(void);

	bool Collision_Line(float& fX, float* pY);
	void Create_Stage(void);
	CLine* Create_StartLine(void);
	void Create_Land1(void);
	void Create_Sky(void);
	void Create_Underground(void);

private:
	list<CLine*> m_LineList;
};

