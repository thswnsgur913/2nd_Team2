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

	m_tInfo.fCX = PlayerSize;
	m_tInfo.fCY = PlayerSize;

	m_fSpeed = 10.f;

	m_bJump = false;
	m_fJumpPower = 15.f;
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
		/*Ellipse(hDC, m_tInfo.fX - 70, m_tInfo.fY + 40, m_tInfo.fX - 10, m_tInfo.fY + 110);//ø¿∏•πﬂ
		Ellipse(hDC, m_tInfo.fX + 10, m_tInfo.fY + 45, m_tInfo.fX + 100, m_tInfo.fY + 90);//øﬁπﬂ
		Ellipse(hDC, m_tInfo.fX + 80, m_tInfo.fY - 10, m_tInfo.fX + 30, m_tInfo.fY + 40);//ø¿∏•∆»
		Ellipse(hDC, m_tInfo.fX - 75, m_tInfo.fY, m_tInfo.fX + 75, m_tInfo.fY - 150);//∏”∏Æ
		Ellipse(hDC, m_tInfo.fX - 80, m_tInfo.fY - 10, m_tInfo.fX - 30, m_tInfo.fY + 40);//øﬁ∆»*/

		Ellipse(hDC, m_tRect.left-20 + iScrollX,  m_tRect.top+40+iScrollY, m_tRect.right-30 + iScrollX, m_tRect.bottom+35 + iScrollY);//øﬁπﬂ
		Ellipse(hDC, m_tRect.left+30 + iScrollX,  m_tRect.top + 40 + iScrollY, m_tRect.right+30 + iScrollX, m_tRect.bottom+20 + iScrollY);//ø¿∏•πﬂ
		Ellipse(hDC, m_tRect.left+40 + iScrollX,  m_tRect.top+10 + iScrollY, m_tRect.right+20 + iScrollX, m_tRect.bottom-10 + iScrollY);//ø¿∏•∆»
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);//∏ˆ≈Î
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
		Ellipse(hDC, m_tRect.left-15 + iScrollX,  m_tRect.top-60 + iScrollY, m_tRect.right+15 + iScrollX, m_tRect.bottom-30 + iScrollY);//∏”∏Æ
		Ellipse(hDC, m_tRect.left-20 + iScrollX,  m_tRect.top+10 + iScrollY, m_tRect.right-40 + iScrollX, m_tRect.bottom-10 + iScrollY);//øﬁ∆»
	    //ø¿∏•¬ ¿Ãµø ∑£¥ı
	}
	if (m_Dir == false)
	{
		/*Ellipse(hDC, m_tInfo.fX + 10, m_tInfo.fY + 40, m_tInfo.fX + 70, m_tInfo.fY + 110);//ø¿∏•πﬂ
		Ellipse(hDC, m_tInfo.fX - 100, m_tInfo.fY + 45, m_tInfo.fX - 10, m_tInfo.fY + 90);//øﬁπﬂ
		Ellipse(hDC, m_tInfo.fX - 80, m_tInfo.fY - 10, m_tInfo.fX - 30, m_tInfo.fY + 40);//øﬁ∆»
		Ellipse(hDC, m_tInfo.fX - 75, m_tInfo.fY, m_tInfo.fX + 75, m_tInfo.fY - 150);//∏”∏Æ
		Ellipse(hDC, m_tInfo.fX + 80, m_tInfo.fY - 10, m_tInfo.fX + 30, m_tInfo.fY + 40);//ø¿∏•∆»*/

		Ellipse(hDC, m_tRect.left - 30 + iScrollX, m_tRect.top + 40, m_tRect.right - 30 + iScrollX, m_tRect.bottom + 20);//øﬁπﬂ
		Ellipse(hDC, m_tRect.left + 30 + iScrollX, m_tRect.top + 40, m_tRect.right + 20 + iScrollX, m_tRect.bottom + 35);//ø¿∏•πﬂ
		Ellipse(hDC, m_tRect.left - 20 + iScrollX, m_tRect.top + 10, m_tRect.right - 40 + iScrollX, m_tRect.bottom - 10);//øﬁ∆»
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);//∏ˆ≈Î
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
		Ellipse(hDC, m_tRect.left - 15 + iScrollX, m_tRect.top - 60, m_tRect.right + 15 + iScrollX, m_tRect.bottom - 30);//∏”∏Æ
		Ellipse(hDC, m_tRect.left + 40 + iScrollX, m_tRect.top + 10, m_tRect.right + 20 + iScrollX, m_tRect.bottom - 10);//ø¿∏•∆»
		//øﬁ¬ ¿Ãµø∑ª¥ı
	}

	//int	iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

}

void CPlayer::Release(void)
{
}

void CPlayer::CollisionEnter(CObj* _sour)
{
	/*if (_sour== )
	{
		//m_tPstat.m_Life -= 1;
	}*/
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
		/*if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))//¥ÎΩ√ ¥©∏£∞Ì ¿÷¿∏∏È º”µµ ¡ı∞°
		{
			m_fSpeed += 10;
			if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT))//πˆ∆∞ãÛ∏È º”µµ 10¿∏∑Œ∫π±Õ
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

		//if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))//¥ÎΩ√ ¥©∏£∞Ì¿÷¿∏∏È º”µµ¡ı∞°
			//m_fSpeed += 5;
		//if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT))//πˆ∆∞ãÛ∏È º”µµ 10¿∏∑Œ∫π±Õ
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

	// ∂Û¿Œ √º≈©øÎ.
	if (iOffSetX + iItv < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Scroll()->Set_ScrollX(-m_fSpeed);

	if (iOffSetY - iItv2 > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Scroll()->Set_ScrollY(m_fSpeed);

	if (iOffSetY + iItv2 < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Scroll()->Set_ScrollY(-m_fSpeed);
}