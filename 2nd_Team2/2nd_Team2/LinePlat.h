#pragma once
#include "Line.h"
#include "Include.h"
#include "Obj.h"

class CLinePlat : public CObj
{
public:
	CLinePlat();
	CLinePlat(vector<LINEPOINT>);
	~CLinePlat();

	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void CollisionEnter(CObj*);
	void Release(void);

	bool Collision_Line(CObj*);
	CLinePlat* Get_LinePlat(void) { return this; }

private:
	list<CLine*> m_LineList;
};


