#include "stdafx.h"
#include "CollisionMgr.h"
#include "LinePlat.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_ColRect()), &(Sour->Get_ColRect())))
			{
				Dest->CollisionEnter(Sour);
				Sour->CollisionEnter(Dest);
			}
		}
	}
}

void CCollisionMgr::Collision_ObjListRect(CObj* _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	if (!_Dest)
	{
		return;
	}


	for (auto& Sour : _Sour)
	{
		if (IntersectRect(&rc, &(_Dest->Get_ColRect()), &(Sour->Get_ColRect())))
		{
			_Dest->CollisionEnter(Sour);
			Sour->CollisionEnter(_Dest);
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{
	
	// abs : 절대값을 구해주는 함수
	float	fWidth  = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fWidth + pSour->Get_Info().fWidth) * 0.5f;

	return fRadius > fDiagonal;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->CollisionEnter(Sour);
				Sour->CollisionEnter(Dest);
			}
		}
	}
}

void CCollisionMgr::Collision_Plat(list<CLinePlat*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest) {
		for (auto& Sour : _Sour) {
			Dest->Collision_Line(Sour);
		}
	}
}

void CCollisionMgr::Collision_OBJLINE(CObj * pObj, CObj* Wall)
{
	LINEPOINT POINT1 = static_cast<CObjLine*>(Wall)->Get_Point1();
	LINEPOINT POINT2 = static_cast<CObjLine*>(Wall)->Get_Point2();
	bool m_bOnLeft = static_cast<CObjLine*>(Wall)->Get_bLeft(); 
	bool m_bOnRight = static_cast<CObjLine*>(Wall)->Get_bRight();

	if ((pObj->Get_Info().fX > POINT1.fX) && (pObj->Get_Info().fX - pObj->Get_Info().fWidth * 0.5) < POINT1.fX)
	{
		m_bOnRight = true;
	}
	else if ((pObj->Get_Info().fX < POINT1.fX) && (pObj->Get_Info().fX + pObj->Get_Info().fWidth * 0.5) > POINT1.fX)
	{
		m_bOnLeft = true;
	}
	else
	{
		m_bOnLeft = false;
		m_bOnRight = false;
	}

	// OBJ를 오른쪽으로 튕겨냄.(POINT1이 위에)

	if ((POINT1.fY < POINT2.fY) && (pObj->Get_Info().fY > POINT1.fY))
	{
		if (m_bOnRight)
		{
			pObj->Set_pos((POINT1.fX + pObj->Get_Info().fWidth * 0.5 + 1.f), pObj->Get_Info().fY);
			m_bOnLeft = false;
			m_bOnRight = false;
		}
	}
	// OBJ를 왼쪽으로 튕겨냄.(POINT2가 위에)
	else if (POINT2.fY < POINT1.fY && (pObj->Get_Info().fY > POINT2.fY))
	{
		if (m_bOnLeft)
		{
			pObj->Set_pos((POINT1.fX - pObj->Get_Info().fWidth * 0.5), pObj->Get_Info().fY);
			m_bOnLeft = false;
			m_bOnRight = false;
		}
	}

}