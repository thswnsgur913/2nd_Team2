#include "stdafx.h"
#include "BehaviorA.h"
#include "BmpMgr.h"

CBehaviorA::CBehaviorA()
{
}

CBehaviorA::CBehaviorA(float _Temp)
{
	m_fXPoint = _Temp;
}

CBehaviorA::~CBehaviorA()
{
	Release();
}

void CBehaviorA::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BatL.bmp", L"MonsterA");
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
}

void CBehaviorA::Release(void)
{

}

void CBehaviorA::Render(HDC hDC)
{
	CBmpMgr::Destroy_Instance();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BatL.bmp", L"MonsterA");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MonsterA");


	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tScrollRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tScrollRect.top),
		int(m_tInfo.fWidth),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fHeight),
		hMemDC,								// ��Ʈ���� ������ �ִ� DC
		0,									// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		(int)m_tInfo.fWidth,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fHeight,
		RGB(255, 255, 253));			// �����ϰ��� �ϴ� ����
}

void CBehaviorA::BehaviorEnter()
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
		if (TargetMove())
		{
			behaviorState = Exit;
			return;
		}
		break;

	case Return:
		if (TargetMoveX())
		{
			behaviorState = Exit;
			return;
		}
		break;
	}
}

void CBehaviorA::BehaviorExit()
{
	
	if (m_dwTime + 2000 < GetTickCount())
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
