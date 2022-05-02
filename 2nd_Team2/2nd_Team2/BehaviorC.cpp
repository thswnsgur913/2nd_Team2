#include "stdafx.h"
#include "BehaviorC.h"


CBehaviorC::CBehaviorC()
{
}

CBehaviorC::CBehaviorC(float _Temp)
{
	m_fXPoint = _Temp;
}

CBehaviorC::~CBehaviorC()
{
	Release();
}

void CBehaviorC::Initialize(void)
{
	m_tInfo.fX = m_fXPoint;
	m_tInfo.fY = 150.f;
	m_tInfo.fWidth = 50.f;
	m_tInfo.fHeight = 50.f;
	m_tInfo.fColWidth = 50.f;
	m_tInfo.fColHeight = 50.f;
	currentState = Create;
	m_dwTime = GetTickCount();
	m_iHP = 100;
	m_iMaxHP = 100;
	m_fSpeed = 10.f;
	bossShotTimer = new CTimer;
}

void CBehaviorC::Release(void)
{
}

void CBehaviorC::Render(HDC hDC)
{
	Rectangle(hDC, m_tScrollRect.left, m_tScrollRect.top, m_tScrollRect.right, m_tScrollRect.bottom);
}

void CBehaviorC::BehaviorEnter()
{
	if (!m_targetObj)
		return;

	switch (currentState)
	{
	case Create:
		targetPosition.x = appearPosition.x;
		//targetPosition.y = appearPosition.y;

		originPosition.x = targetPosition.x;
		//originPosition.y = targetPosition.y;
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
	if (m_dwTime + 3000 < GetTickCount())
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
