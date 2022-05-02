#include "stdafx.h"
#include "BehaviorBoss.h"

CBehaviorBoss::CBehaviorBoss()
{
}

CBehaviorBoss::~CBehaviorBoss()
{
	Release();
}

void CBehaviorBoss::Initialize(void)
{
	m_tInfo.fX = /*m_targetObj->Get_Info().fX +*/ 500.f;
	m_tInfo.fY = 250.f;

	m_tInfo.fWidth = 50.f;
	m_tInfo.fHeight = 50.f;

	m_tInfo.fColWidth = 50.f;
	m_tInfo.fColHeight = 50.f;

	m_iHP = 100;
	m_iMaxHP = 100;

	m_fJumpPower = 18.f;
	m_fJumpTime = 0.f;

	m_fSpeed = 10.f;

	m_bJump = false;

	bossShotTimer = new CTimer;

	currentState = Create;
}

void CBehaviorBoss::Release(void)
{
}

void CBehaviorBoss::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();
	Rectangle(hDC, (m_tRect.left + iScrollX), (m_tRect.top + iScrollY), (m_tRect.right + iScrollX), (m_tRect.bottom + iScrollY));
}

void CBehaviorBoss::BehaviorEnter()
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

	case Pattern1:
		targetPosition.x = m_targetObj->Get_Info().fX;
		targetPosition.y = (m_targetObj->Get_Info().fY);

		originPosition.x = m_tInfo.fX;
		originPosition.y = m_tInfo.fY;
		break;

	case Return:
		targetPosition.x = originPosition.x;
		targetPosition.y = originPosition.y;
		break;

	case Pattern2:
		m_fY = m_tInfo.fY;
		m_bJump = true;
		break;

	case Pattern3:
		bossShotTimer->StartTimer(0.5f, [&]() { ShootPattern3(); });
		break;

	case Pattern4:
		bossShotTimer->StartTimer(0.5f, [&]() { ShootPattern4(); });
		break;

	case Idle:		
		break;
	}

	behaviorState = Execute;
}

void CBehaviorBoss::BehaviorExecute()
{
	if (!m_targetObj)
		return;

	switch (currentState) {
	case Create:
		behaviorState = Exit;
		break;

	case Pattern1:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Return:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Pattern2:
		if (Jumping()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Pattern3:
	case Pattern4:
		bossShotTimer->Update();
		break;

	case Idle:
		behaviorState = Exit;
		break;
	}
}

void CBehaviorBoss::BehaviorExit()
{
	switch (currentState) {
	case Pattern1:
		currentState = Return;
		break;

	case Create:
	case Return:
	case Pattern2:
	case Pattern3:
	case Pattern4:
		currentState = Idle;
		break;

	case Idle:
		RandomPattern();
		break;
	}

	behaviorState = Enter;
}

bool CBehaviorBoss::Jumping()
{
	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower *m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.1f;

		return false;
	}
	
	return true;
}

void CBehaviorBoss::RandomPattern()
{
	srand((unsigned int)time((nullptr)));

	int RandomPattern = rand() % 4 + 1;

	switch (RandomPattern)
	{
	case 1:
		currentState = Pattern1;
		return;

	case 2:
		currentState = Pattern2;
		return;

	case 3:
		currentState = Pattern3;
		return;

	case 4:
		currentState = Pattern4;
		return;
	}
}

bool CBehaviorBoss::Dir()
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

void CBehaviorBoss::ShootPattern3()
{
	if (Dir())
	{
		int shotAngle = 1;
		for (int i = 0; i < 3; ++i)
		{
			Fire(baseShotAngle + shotAngle, DIR_LEFT);
			shotAngle += 40;
		}
		behaviorState = Exit;
	}
	else
	{
		int shotAngle = -1;
		for (int i = 0; i < 3; ++i)
		{
			Fire(baseShotAngle + shotAngle, DIR_RIGHT);
			shotAngle -= 20;
		}
		behaviorState = Exit;
	}
}

void CBehaviorBoss::ShootPattern4()
{
		if (Dir())
		{
			int shotAngle = 1;
			for (int i = 0; i < 5; ++i)
			{
				Fire(baseShotAngle + shotAngle, DIR_LEFT);
				shotAngle += 20;
			}
			behaviorState = Exit;
		}
		else
		{
			int shotAngle = -1;
			for (int i = 0; i < 5; ++i)
			{
				Fire(baseShotAngle + shotAngle, DIR_RIGHT);
				shotAngle -= 15;
			}
			behaviorState = Exit;
		}
}
