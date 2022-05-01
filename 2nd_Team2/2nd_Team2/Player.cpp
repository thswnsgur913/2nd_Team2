#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"


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
	m_tPstat = { 5,3,true };

	m_tInfo.fX = 100.f;
	m_tInfo.fY = WINCY - PlayerSize-500 ;
	m_iHP = 100;
	m_iMaxHP = 100;

	m_tInfo.fWidth = PlayerSize;
	m_tInfo.fHeight = PlayerSize;

	m_tInfo.fColWidth = 80.f;
	m_tInfo.fColHeight = 130.f;

	m_fSpeed = 10.f;

	m_bJump = false;
	m_fJumpPower = 20.f;
	m_fJumpTime = 0.f;

	m_Dir = true;

}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	KeyInput();
	Jumping();

	OffSet();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	
}

void CPlayer::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();
	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

	if (m_Dir == true)
	{
		/*Ellipse(hDC, m_tInfo.fX - 70, m_tInfo.fY + 40, m_tInfo.fX - 10, m_tInfo.fY + 110);//오른발
		Ellipse(hDC, m_tInfo.fX + 10, m_tInfo.fY + 45, m_tInfo.fX + 100, m_tInfo.fY + 90);//왼발
		Ellipse(hDC, m_tInfo.fX + 80, m_tInfo.fY - 10, m_tInfo.fX + 30, m_tInfo.fY + 40);//오른팔
		Ellipse(hDC, m_tInfo.fX - 75, m_tInfo.fY, m_tInfo.fX + 75, m_tInfo.fY - 150);//머리
		Ellipse(hDC, m_tInfo.fX - 80, m_tInfo.fY - 10, m_tInfo.fX - 30, m_tInfo.fY + 40);//왼팔*/

		Ellipse(hDC, m_tRect.left - 20 + iScrollX, m_tRect.top + 40 + iScrollY, m_tRect.right - 30 + iScrollX, m_tRect.bottom + 35 + iScrollY);//왼발
		Ellipse(hDC, m_tRect.left + 30 + iScrollX, m_tRect.top + 40 + iScrollY, m_tRect.right + 30 + iScrollX, m_tRect.bottom + 20 + iScrollY);//오른발
		Ellipse(hDC, m_tRect.left + 40 + iScrollX, m_tRect.top + 10 + iScrollY, m_tRect.right + 20 + iScrollX, m_tRect.bottom - 10 + iScrollY);//오른팔
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);//몸통
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
		Ellipse(hDC, m_tRect.left - 15 + iScrollX, m_tRect.top - 60 + iScrollY, m_tRect.right + 15 + iScrollX, m_tRect.bottom - 30 + iScrollY);//머리
		Ellipse(hDC, m_tRect.left - 20 + iScrollX, m_tRect.top + 10 + iScrollY, m_tRect.right - 40 + iScrollX, m_tRect.bottom - 10 + iScrollY);//왼팔
	    //오른쪽이동 랜더
	}
	if (m_Dir == false)
	{
		/*Ellipse(hDC, m_tInfo.fX + 10, m_tInfo.fY + 40, m_tInfo.fX + 70, m_tInfo.fY + 110);//오른발
		Ellipse(hDC, m_tInfo.fX - 100, m_tInfo.fY + 45, m_tInfo.fX - 10, m_tInfo.fY + 90);//왼발
		Ellipse(hDC, m_tInfo.fX - 80, m_tInfo.fY - 10, m_tInfo.fX - 30, m_tInfo.fY + 40);//왼팔
		Ellipse(hDC, m_tInfo.fX - 75, m_tInfo.fY, m_tInfo.fX + 75, m_tInfo.fY - 150);//머리
		Ellipse(hDC, m_tInfo.fX + 80, m_tInfo.fY - 10, m_tInfo.fX + 30, m_tInfo.fY + 40);//오른팔*/

		Ellipse(hDC, m_tRect.left - 30 + iScrollX, m_tRect.top + 40 + iScrollY, m_tRect.right - 30 + iScrollX, m_tRect.bottom + 20 + iScrollY);//왼발
		Ellipse(hDC, m_tRect.left + 30 + iScrollX, m_tRect.top + 40 + iScrollY, m_tRect.right + 20 + iScrollX, m_tRect.bottom + 35 + iScrollY);//오른발
		Ellipse(hDC, m_tRect.left - 20 + iScrollX, m_tRect.top + 10 + iScrollY, m_tRect.right - 40 + iScrollX, m_tRect.bottom - 10 + iScrollY);//왼팔
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);//몸통
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
		Ellipse(hDC, m_tRect.left - 15 + iScrollX, m_tRect.top - 60 + iScrollY, m_tRect.right + 15 + iScrollX, m_tRect.bottom - 30 + iScrollY);//머리
		Ellipse(hDC, m_tRect.left + 40 + iScrollX, m_tRect.top + 10 + iScrollY, m_tRect.right + 20 + iScrollX, m_tRect.bottom - 10 + iScrollY);//오른팔
		//왼쪽이동렌더
	}

	//int	iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

}

void CPlayer::Release(void)
{
}

void CPlayer::CollisionEnter(CObj* _sour)
{
	//CBullet* bulletObj = dynamic_cast<CBullet*>(_sour);

	if (dynamic_cast<CBullet*>(_sour))
	{
		// 플레이어와 총알이 충돌
		CBullet* bulletObj = dynamic_cast<CBullet*>(_sour);
		if (bulletObj && bulletObj->GetType() == MONSTER_BULLET) {
			bulletObj->Set_Dead();
			
		}
	}
	if (dynamic_cast<CMonster*>(_sour))
	{
		// 플레이어와 몬스터가 충돌
	}
	if(m_tPstat.m_Life<=0)
	{
		m_bDead = true;
		CObjManager::Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CEffect>::Create((float)m_tInfo.fX, (float)m_tInfo.fY));
	}
}

void CPlayer::KeyInput(void)
{
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		/*if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if(GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else*/
		/*if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))//대시 누르고 있으면 속도 증가
		{
			m_fSpeed += 10;
			if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT))//버튼뗴면 속도 10으로복귀
			{
				m_fSpeed = 10.f;
			}
		}*/

		m_Dir = false;
		m_tInfo.fX -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		/*if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else*/

		//if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))//대시 누르고있으면 속도증가
			//m_fSpeed += 5;
		//if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT))//버튼뗴면 속도 10으로복귀
			//m_fSpeed = 10.f;

		m_Dir = true;
		m_tInfo.fX += m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		if (m_tPstat.m_Hammer==true&&m_Dir == true)
		{
			CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CHammer>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_RIGHT));
		}
		if (m_tPstat.m_Hammer == true && m_Dir == false)
		{
			CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CHammer>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_LEFT));
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
		return;
	}
}
void CPlayer::Jumping(void)
{
	float		fY = m_tInfo.fY;

	bool		bLineCol = m_Line->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.2f;
		

		if (bLineCol&&(fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY-PlayerSize*0.5;
		}
	}
	else if (bLineCol)
	{
 		m_tInfo.fY = fY-PlayerSize*0.5;
	}

}

void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int     iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int     iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();
	int		iItv = 30;
	int     iItv2 = 50;


	if (iOffSetX - iItv > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Scroll()->Set_ScrollX(m_fSpeed);

	// 라인 체크용.
	if (iOffSetX + iItv < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Scroll()->Set_ScrollX(-m_fSpeed);

	if (iOffSetY - iItv2 > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Scroll()->Set_ScrollY(m_fSpeed);

	if (iOffSetY + iItv2 < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Scroll()->Set_ScrollY(-m_fSpeed);
}