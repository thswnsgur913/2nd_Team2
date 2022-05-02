#include "stdafx.h"
#include "BehaviorB.h"
#include "BmpMgr.h"


CBehaviorB::CBehaviorB()
{
}

CBehaviorB::CBehaviorB(float _Temp)
{
	m_fXPoint = _Temp;
}

CBehaviorB::~CBehaviorB()
{
	Release();
}

void CBehaviorB::Initialize(void)
{
	m_tInfo.fX = m_fXPoint;
	m_tInfo.fY = 0.f;
	m_tInfo.fWidth = 54.f;
	m_tInfo.fHeight = 54.f;
	m_tInfo.fColWidth = 54.f;
	m_tInfo.fColHeight = 54.f;
	m_bJump = false;
	m_isGround = false;
	currentState = Create;
	m_dwTime = GetTickCount();
	m_iHP = 10;
	m_iMaxHP = 100;
	m_fJumpPower = 18.f;
	m_fJumpTime = 0.f;
	m_fSpeed = 10.f;

	m_bJump = false;

	currentState = Create;
	
}

void CBehaviorB::Release(void)
{
}

void CBehaviorB::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MonsterB");



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
		RGB(255, 174, 201));			// 제거하고자 하는 색상
	//Rectangle(hDC, m_tScrollRect.left, m_tScrollRect.top, m_tScrollRect.right, m_tScrollRect.bottom);
}

void CBehaviorB::BehaviorEnter()
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

		case Pattern2:
			JumpStart();
			break;
		}

		behaviorState = Execute;
	}
}

void CBehaviorB::BehaviorExecute()
{
	if (!m_targetObj)
		return;

	switch (currentState) {
	case Create:
		behaviorState = Exit;
		break;

	case Pattern2:
		if (Jumping()) {
			behaviorState = Exit;
			return;
		}
		break;
	}
}

void CBehaviorB::BehaviorExit()
{
	if (m_dwTime + 3000 < GetTickCount())
	{
		switch (currentState) {
		case Create:
		case Pattern2:
			currentState = Pattern2;
			break;
		}

		behaviorState = Enter;
		m_dwTime = GetTickCount();
	}
}

bool CBehaviorB::Jumping()
{
	if (!m_bJump)
		return true;

	else
	m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
	m_fJumpTime += 0.2f;
	return false;
}

bool CBehaviorB::Dir()
{
	return false;
}
