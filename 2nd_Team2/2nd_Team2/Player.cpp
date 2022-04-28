#include "stdafx.h"
#include "Player.h"
#include "Monster.h"
#include "AbstractFactory.h"

CPlayer::CPlayer() {
}

CPlayer::~CPlayer()
{
	Release();
	m_bulletList = nullptr;
	m_MonsterList = nullptr;
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = WINCY - PlayerSize - 10;
	m_iHP = 100;
	m_iMaxHP = 100;

	m_tInfo.fCX = PlayerSize;
	m_tInfo.fCY = PlayerSize;

	m_fSpeed = 10.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	KeyInput();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release(void)
{
}

void CPlayer::CollisionEnter(CObj* _sour)
{

}

void CPlayer::KeyInput(void)
{
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if(GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else

		m_tInfo.fX -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX += m_fSpeed;

	}
	else if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	else if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;


	if (GetAsyncKeyState('Z') & 0x0001)
	{
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		
	}
}