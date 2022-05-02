#include "stdafx.h"
#include "BehaviorC.h"
#include "BmpMgr.h"

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
	m_tInfo.fY = 0.f;
	m_tInfo.fWidth = 50.f;
	m_tInfo.fHeight = 50.f;
	m_tInfo.fColWidth = 50.f;
	m_tInfo.fColHeight = 50.f;
	currentState = Create;
	m_dwTime = GetTickCount();
	m_iHP = 10;
	m_iMaxHP = 100;
	m_fSpeed = 10.f;
	bossShotTimer = new CTimer;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BearL.bmp", L"MonsterC");
}

void CBehaviorC::Release(void)
{
}

void CBehaviorC::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MonsterC");


	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_tInfo.fWidth),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fHeight),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		(int)m_tInfo.fWidth,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fHeight,
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
										//Rectangle(hDC, m_tScrollRect.left, m_tScrollRect.top, m_tScrollRect.right, m_tScrollRect.bottom);
	Rectangle(hDC, m_tScrollRect.left, m_tScrollRect.top, m_tScrollRect.right, m_tScrollRect.bottom);
}

void CBehaviorC::BehaviorEnter()
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

		case Pattern3:
			bossShotTimer->StartTimer(0.5f, [&]() { Shoot(); });
			break;
		}

		behaviorState = Execute;
	}
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
		return true; // ������ ���� ����
	}
	else
	{
		return false; // ������ ���� ����
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
