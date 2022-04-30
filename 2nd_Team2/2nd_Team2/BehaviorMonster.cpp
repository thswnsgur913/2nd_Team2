#include "stdafx.h"
#include "BehaviorMonster.h"


CBehaviorMonster::CBehaviorMonster()
{
}

CBehaviorMonster::~CBehaviorMonster()
{
	Release();
}

void CBehaviorMonster::Initialize(void)
{
	m_tInfo.fX = 700.f;
	m_tInfo.fY = 708.f;

	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	m_iHP = 100;
	m_iMaxHP = 100;

	//m_bJump = false;
	m_fJumpPower = 18.f;
	m_fJumpTime = 0.f;

	m_fSpeed = 10.f;

	bossShotTimer = new CTimer;

	currentState = Create;
}

void CBehaviorMonster::Release(void)
{
}

void CBehaviorMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBehaviorMonster::BehaviorEnter()
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
		targetPosition.y = m_targetObj->Get_Info().fY;

		originPosition.x = m_tInfo.fX;
		originPosition.y = m_tInfo.fY;
		if (300 >= m_targetObj->Get_Info().fX) // 플레이어 X 좌표가 200보다 작을 경우, 돌진공격의 좌표점을 제한해 플레이어가 회피 할 수 있는 공간을 남김.
		{
			targetPosition.x = 300;
		}
		break;

	case Return:
		targetPosition.x = originPosition.x;
		targetPosition.y = originPosition.y;
		break;

	case Pattern2:
		fY = m_tInfo.fY;
		break;

	case Pattern3: {

		m_iShotCount = 1;
		bossShotTimer->StartTimer(0.5f, [&]() {
			if (m_iShotCount <= 0) {
				behaviorState = Exit;
				return;
			}

			int shotAngle = 100;
			for (int i = 0; i < 3; ++i) {
				Fire(baseShotAngle + shotAngle);
				shotAngle += 20;
			}

			--m_iShotCount;
		});
	}
				   break;

	case Pattern4: {

		m_iShotCount = 1;
		bossShotTimer->StartTimer(0.5f, [&]() {
			if (m_iShotCount <= 0) {
				behaviorState = Exit;
				return;
			}

			int shotAngle = 100;
			for (int i = 0; i < 5; ++i) {
				Fire(baseShotAngle + shotAngle);
				shotAngle += 15;
			}

			--m_iShotCount;
		});
	}
				   break;

	case Idle:
		
		break;
	}

	behaviorState = Execute;
}

void CBehaviorMonster::BehaviorExecute()
{
	switch (currentState) {
	case Create:
		behaviorState = Exit;
		break;

	case Pattern1:
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

void CBehaviorMonster::BehaviorExit()
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

bool CBehaviorMonster::Jumping()
{

	//bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	//if (m_bJump)
	//{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.1f;

		if (/*bLineCol &&*/ (fY < m_tInfo.fY))
		{
			//m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY;
			return true;
		}
		return false;
	//}
	/*else if (bLineCol)
	{
		targetPosition.y = fY;
	}*/
}

void CBehaviorMonster::RandomPattern()
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
