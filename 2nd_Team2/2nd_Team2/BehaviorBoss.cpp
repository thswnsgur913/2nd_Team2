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
	m_bJump = false;
	m_fJumpPower = 15.f;
	m_fJumpTime = 0.f;
}

void CBehaviorBoss::Release(void)
{
}

void CBehaviorBoss::Render(HDC hDC)
{
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
		if (m_targetObj) 
		{
			targetPosition.x = m_targetObj->Get_Info().fX;
			targetPosition.y = m_targetObj->Get_Info().fY;
		}
		else 
		{
			targetPosition.x = originPosition.x;
			targetPosition.y = originPosition.y;
		}
		break;
	case Return:
		targetPosition.x = originPosition.x;
		targetPosition.y = originPosition.y;
		break;

	case Pattern2:
		Jumping();
		break;

	case Pattern3: {

		m_iShotCount = 1;
		bossShotTimer->StartTimer(0.5f, [&]() {
			if (m_iShotCount <= 0) {
				behaviorState = Exit;
				return;
			}

			int shotAngle = 60;
			for (int i = 0; i < 3; ++i) {
				Fire(baseShotAngle + shotAngle);
				shotAngle -= 10;
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

			int shotAngle = 75;
			for (int i = 0; i < 3; ++i) {
				Fire(baseShotAngle + shotAngle);
				shotAngle -= 10;
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

void CBehaviorBoss::BehaviorExecute()
{
	switch (currentState) {
	case Create:
	case Pattern2:
	case Return:
		if (TargetMove()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Pattern1:
	case Pattern3:
	case Pattern4:
	case Idle:
		bossShotTimer->Update();
		break;
	}
}

void CBehaviorBoss::BehaviorExit()
{
	switch (currentState) {
	case Create:
	case Pattern1:
	case Pattern3:
	case Pattern4:
	case Return:
		currentState = Idle;
		break;

	case Pattern2:
		currentState = Return;
		break;

	case Idle:
		RandomPattern();
		break;
	}

	behaviorState = Enter;
}

void CBehaviorBoss::Jumping()
{
	float		fY = 0.f;

	//bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		targetPosition.y -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.2f;

		/*if (bLineCol && (fY < targetPosition.y))
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			targetPosition.y = fY;
		}*/
	}
	/*else if (bLineCol)
	{
		targetPosition.y = fY;
	}*/
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
