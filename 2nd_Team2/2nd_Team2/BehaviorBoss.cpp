#include "stdafx.h"
#include "BehaviorBoss.h"
#include "BmpMgr.h"

CBehaviorBoss::CBehaviorBoss()
{
}

CBehaviorBoss::CBehaviorBoss(float _Temp)
{
	m_fXPoint = _Temp;
}

CBehaviorBoss::~CBehaviorBoss()
{
	Release();
}

void CBehaviorBoss::Initialize(void)
{
	m_tInfo.fX = m_fXPoint;
	m_tInfo.fY = 0.f;
	m_tInfo.fWidth = 50.f;
	m_tInfo.fHeight = 50.f;
	m_tInfo.fColWidth = 50.f;
	m_tInfo.fColHeight = 50.f;
	m_bJump = false;
	m_isGround = false;
	currentState = Create;
	m_dwTime = GetTickCount();
	m_iHP = 100;
	m_iMaxHP = 100;
	m_fJumpPower = 18.f;
	m_fJumpTime = 0.f;
	m_fSpeed = 10.f;
	bossShotTimer = new CTimer;

	currentState = Create;

}

void CBehaviorBoss::Release(void)
{
}

void CBehaviorBoss::Render(HDC hDC)
{
	CBmpMgr::Destroy_Instance();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DragonL.bmp", L"BossMonster");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossMonster");
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tScrollRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tScrollRect.top),
		int(m_tInfo.fWidth),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fHeight),
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		(int)m_tInfo.fWidth,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fHeight,
		RGB(255, 255, 255));			// 제거하고자 하는 색상
	   // Rectangle(hDC, m_tScrollRect.left, m_tScrollRect.top, m_tScrollRect.right, m_tScrollRect.bottom);
}

void CBehaviorBoss::BehaviorEnter()
{
	if (!m_targetObj)
		return;

	if (360.f >= (m_tInfo.fX - m_targetObj->Get_Info().fX))
	{
		switch (currentState)
		{
		case Create:
			targetPosition.x = appearPosition.x;
			//targetPosition.y = appearPosition.y;

			originPosition.x = targetPosition.x;
			//originPosition.y = targetPosition.y;
			break;

		case Pattern1:
			targetPosition.x = m_targetObj->Get_Info().fX;
			//targetPosition.y = m_targetObj->Get_Info().fY;

			originPosition.x = m_tInfo.fX;
			//originPosition.y = m_tInfo.fY;
			break;

		case Return:
			targetPosition.x = originPosition.x;
			//targetPosition.y = originPosition.y;
			break;

		case Pattern2:
			JumpStart();
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
		if (TargetMoveX()) {
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
	if (m_dwTime + 2000 < GetTickCount())
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
	}

	behaviorState = Enter;
}

bool CBehaviorBoss::Jumping()
{
	if (!m_bJump)
		return true;

	else
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
	m_fJumpTime += 0.2f;
	return false;
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
