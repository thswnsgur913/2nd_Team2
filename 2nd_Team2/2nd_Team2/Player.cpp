#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "MainGame.h"
#include "LinePlat.h"
#include "BmpMgr.h"


CPlayer::CPlayer():
	GodModeSecond(5.f) {
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tPstat = { 5,3,false,false };

	m_tInfo.fX = 100.f;
	//m_tInfo.fY = WINCY - PlayerSize-500 ;
	m_tInfo.fY = WINCY - 250.f;

	m_tInfo.fWidth = PlayerSize;
	m_tInfo.fHeight = PlayerSize;

	m_tInfo.fColWidth = 80.f;
	m_tInfo.fColHeight = 130.f;

	m_fSpeed = PlayerSpeed;

	m_bJump = true;
	m_fJumpPower = 14.f;
	m_fJumpTime = 0.f;
	m_fDropTime = 0.f;

	m_isGround = false;

	m_Dir = true;

	m_GodMode = false;

	m_godModeTimer = new CTimer;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/KirbyNormalR.bmp", L"Player");

}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	KeyInput();

	OffSet();
	
	Drop();
	Jumping();

	m_godModeTimer->Update();

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

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerNormalL");;

	if (m_GodMode == true && m_Dir == true)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerSuperR");
	}
	else if (m_GodMode == true && m_Dir == false)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerSuperL");
	}
	else
	{
		if (m_tPstat.m_Hammer == false && m_tPstat.m_Lance == true && m_Dir == true)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerWingR");
		}
		else if (m_tPstat.m_Hammer == false && m_tPstat.m_Lance == true && m_Dir == false)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerWingL");
		}
		else if (m_tPstat.m_Hammer == true && m_tPstat.m_Lance == false && m_Dir == true)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerR");
		}

		else if (m_tPstat.m_Hammer == false && m_tPstat.m_Lance == false && m_Dir == true)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerNormalR");
		}

		else if (m_tPstat.m_Hammer == true && m_tPstat.m_Lance == false && m_Dir == false)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerL");
		}
		else if (m_tPstat.m_Hammer == false && m_tPstat.m_Lance == false && m_Dir == false)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerNormalL");
		}
	}

	GdiTransparentBlt(hDC,
		int(m_tRect.left + iScrollX),
		int(m_tRect.top +iScrollY),
		int(m_tInfo.fWidth),
		int(m_tInfo.fHeight),
		hMemDC,
		0,
		0,
		(int)m_tInfo.fWidth,
		(int)m_tInfo.fHeight,
		RGB(255, 255, 255));

}

void CPlayer::Release(void)
{
}


void CPlayer::Set_PosX(float _fA)
{
	m_tInfo.fX = _fA;
}

void CPlayer::CollisionEnter(CObj* _sour)
{

	CMonster* MonsterObj = dynamic_cast<CMonster*>(_sour);
	//CBullet* bulletObj = dynamic_cast<CBullet*>(_sour);

	if (dynamic_cast<CBullet*>(_sour))
	{
		// 플레이어와 총알이 충돌
		CBullet* bulletObj = dynamic_cast<CBullet*>(_sour);
		if (bulletObj && bulletObj->GetType() == MONSTER_BULLET) 
		{
			if (m_GodMode == true)
			{
				bulletObj->Set_Dead();
			}
			else if (m_GodMode == false)
			{
				bulletObj->Set_Dead();
				Set_Damage();
			}
		}
	}
	
	if (MonsterObj)
	{
		// 플레이어와 몬스터가 충돌
		if (m_GodMode == true)
		{
			MonsterObj->Set_Dead();
		}
		else if (m_GodMode == false)
		{
			
			Set_Damage();
			if (m_Dir==true)
			{
				m_tInfo.fX -= 30;
			}
			else
			{
				m_tInfo.fX += 30;
			}
		}
	}

	if(CMainGame::Life<=0)
	{
		m_bDead = true;
	}

}

void CPlayer::Set_Damage()
{
	//CObjManager::Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CEffect>::Create((float)m_tInfo.fX, (float)m_tInfo.fY));
	CMainGame::DeadTime -= 5.f;

	//m_tInfo.fX = 100.f;
	//m_tInfo.fY = WINCY - 250.f;

}

void CPlayer::KeyInput(void)
{
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{

		if (CKeyMgr::Get_Instance()->Key_Up('Z'))
		{
			if (m_tPstat.m_Hammer == true && m_Dir == true)
			{
				CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CHammer>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_RIGHT,m_fSpeed+5));
			}
			if (m_tPstat.m_Hammer == true && m_Dir == false)
			{
				CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CHammer>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_LEFT,m_fSpeed+5));
			}
			if (m_tPstat.m_Lance == true && m_Dir == true)
			{
				CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CLance>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_RIGHT));
			}
			if (m_tPstat.m_Lance == true && m_Dir == false)
			{
				CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CLance>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_LEFT));
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			JumpStart();
			return;
		}

		m_Dir = false;
		m_tInfo.fX -= m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		if (m_fSpeed<15)
		{
			m_fSpeed += 0.1f;
			
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT))
	{
		m_fSpeed = PlayerSpeed;
	}

	else if (GetAsyncKeyState(VK_RIGHT))
	{

		if (CKeyMgr::Get_Instance()->Key_Up('Z'))
		{
			if (m_tPstat.m_Hammer == true && m_Dir == true)
			{
				CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CHammer>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_RIGHT, m_fSpeed+5));
			}
			if (m_tPstat.m_Hammer == true && m_Dir == false)
			{
				CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CHammer>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_LEFT, m_fSpeed+5));
			}
			if (m_tPstat.m_Lance == true && m_Dir == true)
			{
				CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CLance>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_RIGHT));
			}
			if (m_tPstat.m_Lance == true && m_Dir == false)
			{
				CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CLance>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_LEFT));
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			JumpStart();
			return;
		}

		m_Dir = true;
		m_tInfo.fX += m_fSpeed;

	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		if (m_fSpeed<15)
		{
			m_fSpeed += 0.1f;
		}
	}
 	 if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT))
	{
		m_fSpeed = PlayerSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Up('Z'))
	{
		if (m_tPstat.m_Hammer==true&&m_Dir == true)
		{
			CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CHammer>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_RIGHT,m_fSpeed));
		}
		if (m_tPstat.m_Lance == true && m_Dir == true)
		{
			CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CLance>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_RIGHT));
		}
		if (m_tPstat.m_Hammer == true && m_Dir == false)
		{
			CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CHammer>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_LEFT, m_fSpeed));
		}
		if (m_tPstat.m_Lance == true && m_Dir == false)
		{
			CObjManager::Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CLance>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_LEFT));
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		JumpStart();
		return;
	}
}

void CPlayer::GodMode(void)
{

	m_godModeTimer->StartTimer(GodModeSecond, [&]() {m_GodMode = false; m_godModeTimer->StopTimer();});
}

void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int     iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int     iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();
	int		iItv = 300;
	int     iItv2 = 100;


	if ((iOffSetX - iItv <= m_tInfo.fX + iScrollX)&& (iOffSetX >= m_tInfo.fX + iScrollX))
		CScrollMgr::Get_Scroll()->Set_ScrollX(-m_fSpeed);

	// 왼쪽으로 스크롤은 금지.(왼쪽으로 이동불가),현재는 테스트용으로 존재
	if (iOffSetX - iItv - 10> m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Scroll()->Set_ScrollX(m_fSpeed);

	if (iOffSetY - iItv2 >= m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Scroll()->Set_ScrollY(m_fSpeed);

	if (iOffSetY + iItv2 < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Scroll()->Set_ScrollY(-m_fSpeed);
}

