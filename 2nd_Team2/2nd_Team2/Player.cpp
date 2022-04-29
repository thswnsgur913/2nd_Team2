#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "ObjManager.h"

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
	m_tInfo.fX = 300.f;
	m_tInfo.fY = WINCY - PlayerSize-168 ;
	m_iHP = 100;
	m_iMaxHP = 100;

	m_tInfo.fCX = PlayerSize;
	m_tInfo.fCY = PlayerSize;

	m_fSpeed = 10.f;

	m_bJump = false;
	m_fJumpPower = 15.f;
	m_fJumpTime = 0.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	KeyInput();
	Jumping();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC hDC)
{
	Ellipse(hDC, m_tInfo.fX - 70, m_tInfo.fY+40, m_tInfo.fX-10, m_tInfo.fY+110);//¿À¸¥¹ß

	Ellipse(hDC, m_tInfo.fX + 10, m_tInfo.fY+45, m_tInfo.fX +100, m_tInfo.fY +90);//¿Þ¹ß

	Ellipse(hDC, m_tInfo.fX + 80, m_tInfo.fY - 10, m_tInfo.fX + 30, m_tInfo.fY + 40);//¿À¸¥ÆÈ
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);//¸öÅë
	Ellipse(hDC, m_tInfo.fX-75, m_tInfo.fY, m_tInfo.fX+75, m_tInfo.fY -150);//¸Ó¸®
	Ellipse(hDC, m_tInfo.fX-80, m_tInfo.fY-10, m_tInfo.fX-30, m_tInfo.fY+40);//¿ÞÆÈ

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
		CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_RIGHT));
	}

	/*if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		m_bJump = true;
		return;
	}*/
	if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		m_bJump = true;
		return;
	}
}
void CPlayer::Jumping(void)
{
	float		fY =500.f;

	//bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.2f;

		if (fY < m_tInfo.fY)
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY;
	    }
	}

	/*	if (bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY;
	}*/
}