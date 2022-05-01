#include "stdafx.h"
#include "BehaviorA.h"


CBehaviorA::CBehaviorA()
{
}


CBehaviorA::~CBehaviorA()
{
	Release();
}

void CBehaviorA::Initialize(void)
{
	m_tInfo.fX = 700.f;
	m_tInfo.fY = 500.f;

	m_tInfo.fWidth = 50;
	m_tInfo.fHeight = 50;

	m_tInfo.fColWidth = 50.f;
	m_tInfo.fColHeight = 50.f;

	m_iHP = 10;
	m_iMaxHP = 10;

	m_fJumpPower = 18.f;
	m_fJumpTime = 0.f;

	m_fSpeed = 10.f;

	m_fY = m_tInfo.fY;
}

void CBehaviorA::Release(void)
{
}

void CBehaviorA::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();
	Rectangle(hDC, (m_tRect.left + iScrollX), (m_tRect.top + iScrollY), (m_tRect.right + iScrollX), (m_tRect.bottom + iScrollY));
}

void CBehaviorA::BehaviorEnter()
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
		if (300 >= m_targetObj->Get_Info().fX) // �÷��̾� X ��ǥ�� 300���� ���� ���, ���������� ��ǥ���� ������ �÷��̾ ȸ�� �� �� �ִ� ������ ����.
		{
			targetPosition.x = 300;
		}
		break;

	case Return:
		targetPosition.x = originPosition.x;
		targetPosition.y = originPosition.y;
		break;
	}

	behaviorState = Execute;
}

void CBehaviorA::BehaviorExecute()
{
	if (!m_targetObj)
		return;

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
	}
}

void CBehaviorA::BehaviorExit()
{
	if (m_dwTime + 5000 < GetTickCount())
	{
		switch (currentState) {
		case Pattern1:
			currentState = Return;
			break;

		case Create:
		case Return:
			currentState = Pattern1;
			break;
		}

		behaviorState = Enter;
		m_dwTime = GetTickCount();
	}
}

bool CBehaviorA::Jumping()
{
	return false;
}

bool CBehaviorA::Dir()
{
	return false;
}
