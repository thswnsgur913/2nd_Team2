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
	m_tInfo.fY = 150.f;

	m_tInfo.fWidth = 50;
	m_tInfo.fHeight = 50;

	m_tInfo.fColWidth = 50.f;
	m_tInfo.fColHeight = 50.f;

	m_iHP = 10;
	m_iMaxHP = 10;

	m_fJumpPower = 18.f;
	m_fJumpTime = 0.f;

	m_fSpeed = 10.f;

	m_bJump = false;

	currentState = Create;
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ScolpionL.bmp", L"MonsterB");
}

void CBehaviorB::Release(void)
{
}

void CBehaviorB::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MonsterB");


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
	Rectangle(hDC, m_tScrollRect.left, m_tScrollRect.top, m_tScrollRect.right, m_tScrollRect.bottom);
}

void CBehaviorB::BehaviorEnter()
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

	case Pattern2:
		//m_fY = m_tInfo.fY;
		m_bJump = true;
		break;
	}

	behaviorState = Execute;
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
	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.1f;

		return false;
	}
	//m_tInfo.fY = m_fY;
	return true;
}

bool CBehaviorB::Dir()
{
	return false;
}
