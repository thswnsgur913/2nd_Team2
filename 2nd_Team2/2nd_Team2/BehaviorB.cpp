#include "stdafx.h"
#include "BehaviorB.h"


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
}

void CBehaviorB::Release(void)
{
}

void CBehaviorB::Render(HDC hDC)
{
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
