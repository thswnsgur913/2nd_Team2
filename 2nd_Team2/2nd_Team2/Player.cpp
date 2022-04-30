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
	//m_tInfo.fY = WINCY - PlayerSize-500 ;
	m_tInfo.fY = WINCY - 250.f;
	m_iHP = 100;
	m_iMaxHP = 100;

	m_tInfo.fCX = PlayerSize;
	m_tInfo.fCY = PlayerSize;

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
		/*Ellipse(hDC, m_tInfo.fX - 70, m_tInfo.fY + 40, m_tInfo.fX - 10, m_tInfo.fY + 110);//������
		Ellipse(hDC, m_tInfo.fX + 10, m_tInfo.fY + 45, m_tInfo.fX + 100, m_tInfo.fY + 90);//�޹�
		Ellipse(hDC, m_tInfo.fX + 80, m_tInfo.fY - 10, m_tInfo.fX + 30, m_tInfo.fY + 40);//������
		Ellipse(hDC, m_tInfo.fX - 75, m_tInfo.fY, m_tInfo.fX + 75, m_tInfo.fY - 150);//�Ӹ�
		Ellipse(hDC, m_tInfo.fX - 80, m_tInfo.fY - 10, m_tInfo.fX - 30, m_tInfo.fY + 40);//����*/

		Ellipse(hDC, m_tRect.left - 20 + iScrollX, m_tRect.top + 40 + iScrollY, m_tRect.right - 30 + iScrollX, m_tRect.bottom + 35 + iScrollY);//�޹�
		Ellipse(hDC, m_tRect.left + 30 + iScrollX, m_tRect.top + 40 + iScrollY, m_tRect.right + 30 + iScrollX, m_tRect.bottom + 20 + iScrollY);//������
		Ellipse(hDC, m_tRect.left + 40 + iScrollX, m_tRect.top + 10 + iScrollY, m_tRect.right + 20 + iScrollX, m_tRect.bottom - 10 + iScrollY);//������
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);//����
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
		Ellipse(hDC, m_tRect.left - 15 + iScrollX, m_tRect.top - 60 + iScrollY, m_tRect.right + 15 + iScrollX, m_tRect.bottom - 30 + iScrollY);//�Ӹ�
		Ellipse(hDC, m_tRect.left - 20 + iScrollX, m_tRect.top + 10 + iScrollY, m_tRect.right - 40 + iScrollX, m_tRect.bottom - 10 + iScrollY);//����
	    //�������̵� ����
	}
	if (m_Dir == false)
	{
		/*Ellipse(hDC, m_tInfo.fX + 10, m_tInfo.fY + 40, m_tInfo.fX + 70, m_tInfo.fY + 110);//������
		Ellipse(hDC, m_tInfo.fX - 100, m_tInfo.fY + 45, m_tInfo.fX - 10, m_tInfo.fY + 90);//�޹�
		Ellipse(hDC, m_tInfo.fX - 80, m_tInfo.fY - 10, m_tInfo.fX - 30, m_tInfo.fY + 40);//����
		Ellipse(hDC, m_tInfo.fX - 75, m_tInfo.fY, m_tInfo.fX + 75, m_tInfo.fY - 150);//�Ӹ�
		Ellipse(hDC, m_tInfo.fX + 80, m_tInfo.fY - 10, m_tInfo.fX + 30, m_tInfo.fY + 40);//������*/

		Ellipse(hDC, m_tRect.left - 30 + iScrollX, m_tRect.top + 40 + iScrollY, m_tRect.right - 30 + iScrollX, m_tRect.bottom + 20 + iScrollY);//�޹�
		Ellipse(hDC, m_tRect.left + 30 + iScrollX, m_tRect.top + 40 + iScrollY, m_tRect.right + 20 + iScrollX, m_tRect.bottom + 35 + iScrollY);//������
		Ellipse(hDC, m_tRect.left - 20 + iScrollX, m_tRect.top + 10 + iScrollY, m_tRect.right - 40 + iScrollX, m_tRect.bottom - 10 + iScrollY);//����
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);//����
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
		Ellipse(hDC, m_tRect.left - 15 + iScrollX, m_tRect.top - 60 + iScrollY, m_tRect.right + 15 + iScrollX, m_tRect.bottom - 30 + iScrollY);//�Ӹ�
		Ellipse(hDC, m_tRect.left + 40 + iScrollX, m_tRect.top + 10 + iScrollY, m_tRect.right + 20 + iScrollX, m_tRect.bottom - 10 + iScrollY);//������
		//�����̵�����
	}

	//int	iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

}

void CPlayer::Release(void)
{
}

void CPlayer::CollisionEnter(CObj* _sour)
{

	CMonster* MonsterObj = dynamic_cast<CMonster*>(_sour);


	if (MonsterObj)
	{
		MonsterObj->Hit();

		--m_tPstat.m_Life;

		m_tInfo.fX = 100.f;
		m_tInfo.fY = WINCY - 250.f;
	}

	if(m_tPstat.m_Life<=0)
	{
		CObjManager::Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CEffect>::Create((float)m_tInfo.fX, (float)m_tInfo.fY));
		m_bDead = true;
	}
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

		m_Dir = false;
		m_tInfo.fX -= m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		if (m_fSpeed<20)
		{
			m_fSpeed += 0.1f;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT))
	{
		m_fSpeed = 10.f;
	}

	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (CKeyMgr::Get_Instance()->Key_Up('Z'))
		{
			if (m_tPstat.m_Hammer == true && m_Dir == true)
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

		m_Dir = true;
		m_tInfo.fX += m_fSpeed;

	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		if (m_fSpeed<20)
		{
			m_fSpeed += 0.1f;
		}
	}
 	 if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT))
	{
		m_fSpeed = 10.f;
	}

	if (CKeyMgr::Get_Instance()->Key_Up('Z'))
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

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
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
			m_tInfo.fY = fY-PlayerSize*0.5f;
		}
	}
	else if (bLineCol)
	{
 		m_tInfo.fY = fY-PlayerSize*0.5f;
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

	// ���� üũ��.
	if (iOffSetX + iItv < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Scroll()->Set_ScrollX(-m_fSpeed);

	if (iOffSetY - iItv2 > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Scroll()->Set_ScrollY(m_fSpeed);

	if (iOffSetY + iItv2 < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Scroll()->Set_ScrollY(-m_fSpeed);
}