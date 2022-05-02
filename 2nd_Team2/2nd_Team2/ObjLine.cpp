#include "stdafx.h"
#include "ObjLine.h"


CObjLine::CObjLine()
{
}

CObjLine::CObjLine(LINEPOINT _LeftP, LINEPOINT _RightP)
	:POINT1(_LeftP),POINT2(_RightP)
{
	m_bOnLeft = false;
	m_bOnRight = false;
}


CObjLine::~CObjLine()
{
	Release();
}

void CObjLine::Initialize(void)
{
	m_tInfo.fWidth = 10.f;
	m_tInfo.fHeight = abs(POINT1.fY - POINT2.fY);
}

int CObjLine::Update(void)
{
	return 0;
}

void CObjLine::Late_Update(void)
{
}

void CObjLine::Render(HDC hDC)
{
	MoveToEx(hDC, (int)(POINT1.fX + CScrollMgr::Get_Scroll()->Get_ScrollX()), (int)(POINT1.fY + CScrollMgr::Get_Scroll()->Get_ScrollY()), nullptr);
	LineTo(hDC, (int)(POINT2.fX + CScrollMgr::Get_Scroll()->Get_ScrollX()), (int)(POINT2.fY + CScrollMgr::Get_Scroll()->Get_ScrollY()));
}

void CObjLine::Release(void)
{
}

void CObjLine::CollisionEnter(CObj * _sour)
{
}

void CObjLine::Collision_OBJLINE(CObj * pObj)
{
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
