#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool		Check_Sphere(CObj* pDest, CObj* pSour);
	static void		Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_ObjListRect(CObj* _Dest, list<CObj*> _Sour);
	static void		Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);
};

