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


	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fWidth),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fHeight),
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		(int)m_tInfo.fWidth,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fHeight,
		RGB(255, 255, 255));			// 제거하고자 하는 색상
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
