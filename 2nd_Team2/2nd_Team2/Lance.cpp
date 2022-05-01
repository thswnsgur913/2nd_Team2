#include "stdafx.h"
#include "Lance.h"


CLance::CLance()
{
}


CLance::~CLance()
{
}

void CLance::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 30.f;

	m_Distance = 0;

	Update_Rect();
}

int CLance::Update()
{

	if (m_bDead)
		return OBJ_DEAD;
	if (m_eDir == DIR_RIGHT)
	{
		//m_tInfo.fX += m_tDir.fX * m_fSpeed;
		//m_tInfo.fY += m_tDir.fY * m_fSpeed;
		m_tInfo.fX += m_fSpeed;
		m_Distance += m_fSpeed;
	}
	if (m_eDir == DIR_LEFT)
	{
		//m_tInfo.fX += m_tDir.fX * -(m_fSpeed);
		//m_tInfo.fY += m_tDir.fY * -(m_fSpeed);
		m_tInfo.fX += -(m_fSpeed);
		m_Distance -= m_fSpeed;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CLance::Late_Update()
{
	//if (m_tRect.left < -100 || m_tRect.right >15000 || m_tRect.top < -5000 || m_tRect.bottom > 15000)
	if (m_Distance>=WINCX|| m_Distance<=-WINCX)
	{
		m_bDead = true;
	}
}

void CLance::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();

	HBRUSH brush;
	HPEN pen;

	if (m_eDir == DIR_RIGHT)
	{

		brush = CreateSolidBrush(RGB(150, 75, 0));
		SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right+50 + iScrollX, m_tRect.bottom + iScrollY);
		brush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left+50 + iScrollX, m_tRect.top + iScrollY, m_tRect.right +50+ iScrollX, m_tRect.bottom + iScrollY);
		DeleteObject(brush);
	}
	else
	{
		brush = CreateSolidBrush(RGB(150, 75, 0));
		SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left - 50 + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
		brush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left-50 + iScrollX, m_tRect.top + iScrollY, m_tRect.right-50  + iScrollX, m_tRect.bottom + iScrollY);
		DeleteObject(brush);
	}
}

void CLance::Release()
{
}

void CLance::CollisionEnter(CObj * _sour)
{
	float		fY = m_tInfo.fY;

	CMonster* collisionMonster = dynamic_cast<CMonster*>(_sour);

	if (collisionMonster && m_eBulletType == PLAYER_BULLET && !collisionMonster->GetDead())
	{
		collisionMonster->Hit();
		m_bDead = true;
	}
}
