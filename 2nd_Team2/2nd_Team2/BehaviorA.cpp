#include "stdafx.h"
#include "BehaviorA.h"


CBehaviorA::CBehaviorA()
{
}


CBehaviorA::~CBehaviorA()
{
	Release();
}

void CBehaviorA::Initialize(void)
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

void CBehaviorA::Release(void)
{
}

void CBehaviorA::Render(HDC hDC)
{
}

void CBehaviorA::BehaviorEnter()
{
}

void CBehaviorA::BehaviorExecute()
{
}

void CBehaviorA::BehaviorExit()
{
}

bool CBehaviorA::Jumping()
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

bool CBehaviorA::Dir()
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
