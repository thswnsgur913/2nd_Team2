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

	bossShotTimer = new CTimer;
}

void CBehaviorC::Release(void)
{
}

void CBehaviorC::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();
	Rectangle(hDC, (m_tRect.left + iScrollX), (m_tRect.top + iScrollY), (m_tRect.right + iScrollX), (m_tRect.bottom + iScrollY));
}

void CBehaviorC::BehaviorEnter()
{
	if (!m_targetObj)
		return;

	switch (currentState)
	{
	case Create:
		targetPosition.x = appearPosition.x;
		targetPosition.y = appearPosition.y;

		originPosition.x = targetPosition.x;
		originPosition.y = targetPosition.y;
		break;

	case Pattern3:
		bossShotTimer->StartTimer(0.5f, [&]() { Shoot(); });
		break;
	}

	behaviorState = Execute;
}

void CBehaviorC::BehaviorExecute()
{
	if (!m_targetObj)
		return;

	switch (currentState) {
	case Create:
		behaviorState = Exit;
		break;

	case Pattern3:
		bossShotTimer->Update();
		break;
	}
}

void CBehaviorC::BehaviorExit()
{
	if (m_dwTime + 5000 < GetTickCount())
	{
		switch (currentState) {
		case Create:
		case Pattern3:
			currentState = Pattern3;
			break;
		}

		behaviorState = Enter;
		m_dwTime = GetTickCount();
	}
}

bool CBehaviorC::Jumping()
{
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

void CBehaviorC::Shoot()
{
	if (Dir())
	{
		Fire(baseShotAngle + 40, DIR_LEFT);
		behaviorState = Exit;
	}
	else
	{
		Fire(baseShotAngle + -40, DIR_RIGHT);		
		behaviorState = Exit;
	}
}
