#include "stdafx.h"
#include "BehaviorC.h"


CBehaviorC::CBehaviorC()
{
}


CBehaviorC::~CBehaviorC()
{
	Release();
}

void CBehaviorC::Initialize(void)
{
	m_tInfo.fX = 700.f;
	m_tInfo.fY = 500.f;

	m_tInfo.fWidth = 50;
	m_tInfo.fHeight = 50;

	m_tInfo.fColWidth = 50.f;
	m_tInfo.fColHeight = 50.f;

	m_iHP = 10;
	m_iMaxHP = 10;

	m_fJumpPower = 18.f;
	m_fJumpTime = 0.f;

	m_fSpeed = 10.f;

	m_fY = m_tInfo.fY;
}

void CBehaviorC::Release(void)
{
}

void CBehaviorC::Render(HDC hDC)
{
}

void CBehaviorC::BehaviorEnter()
{
}

void CBehaviorC::BehaviorExecute()
{
}

void CBehaviorC::BehaviorExit()
{
}

bool CBehaviorC::Jumping()
{
	//fY = m_tInfo.fY;
	//bool bLineCol = m_Line->Collision_Line(m_tInfo.fX, &fY);

	m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
	m_fJumpTime += 0.1f;

	if (/*bLineCol &&*/ (m_fY < m_tInfo.fY))
	{
		m_fJumpTime = 0.f;
		m_tInfo.fY = m_fY;
		return true;
	}
	/*else if (bLineCol)
	{
	m_tInfo.fY = fY;
	}*/
	return false;
}

bool CBehaviorC::Dir()
{
	if (m_tInfo.fX > m_targetObj->Get_Info().fX)
	{
		return true; // 좌측을 향해 공격
	}
	else
	{
		return false; // 우측을 향해 공격
	}
}
