#include "stdafx.h"
#include "Hammer.h"

CHammer::CHammer()
{
}

CHammer::~CHammer()
{
	Release();
}

void CHammer::Initialize()
{
	m_tInfo.fWidth = 10.f;
	m_tInfo.fHeight = 10.f;

	m_tInfo.fColWidth = 50.f;
	m_tInfo.fColHeight = 70.f;

	Update_Rect();

	m_bThrow = true;
	m_fThrowPower = 15.f;
	m_fThrowTime = 0.f;
}

int CHammer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	if (m_eDir == DIR_RIGHT)
	{
		m_tInfo.fX += m_tDir.fX * m_fSpeed;
		m_tInfo.fY += m_tDir.fY * m_fSpeed;
		m_tInfo.fX += m_fSpeed;
	}
	if (m_eDir == DIR_LEFT)
	{
		m_tInfo.fX += m_tDir.fX * -(m_fSpeed);
		m_tInfo.fY += m_tDir.fY * -(m_fSpeed);
		m_tInfo.fX += -(m_fSpeed);
	}
	Throw();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CHammer::Late_Update()
{
	if (m_tRect.top < -5000 || m_tRect.bottom > 15000) 
	{
		m_bDead = true;
	}
}

void CHammer::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();

	HBRUSH brush;
	HGDIOBJ hOldBrush;

	if (m_eDir == DIR_RIGHT)
	{

		brush = CreateSolidBrush(RGB(150, 75, 0));
		hOldBrush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left - 40 + iScrollX, m_tRect.top + iScrollY, m_tRect.right - 40 + iScrollX, m_tRect.bottom - 50 + iScrollY);
		SelectObject(hDC, hOldBrush);
		DeleteObject(brush);

		brush = CreateSolidBrush(RGB(0, 0, 0));
		hOldBrush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left - 70 + iScrollX, m_tRect.top - 40 + iScrollY, m_tRect.right - 10 + iScrollX, m_tRect.bottom - 100 + iScrollY);
		SelectObject(hDC, hOldBrush);
		DeleteObject(brush);

	}
	else
	{
		brush = CreateSolidBrush(RGB(150, 75, 0));
		hOldBrush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left + 40 + iScrollX, m_tRect.top + iScrollY, m_tRect.right +40 + iScrollX, m_tRect.bottom - 50 + iScrollY);
		SelectObject(hDC, hOldBrush);
		DeleteObject(brush);

		brush = CreateSolidBrush(RGB(0, 0, 0));
		hOldBrush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left + 10 + iScrollX, m_tRect.top - 40 + iScrollY, m_tRect.right + 70 + iScrollX, m_tRect.bottom - 100 + iScrollY);
		SelectObject(hDC, hOldBrush);
		DeleteObject(brush);
	}



	//Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tR
}

void CHammer::Release()
{

}

void CHammer::CollisionEnter(CObj * _sour)
{
}

void CHammer::Throw()
{
	float		fY = 15000.f;

	if (m_bThrow)
	{
		m_tInfo.fY -= m_fThrowPower * m_fThrowTime - 9.8f * m_fThrowTime * m_fThrowTime * 0.5f;
		m_fThrowTime += 0.1f;

		if (fY < m_tInfo.fY)
		{
			m_bThrow = false;
			m_fThrowTime = 0.f;
			//m_tInfo.fY = fY;
		}
	}
}


