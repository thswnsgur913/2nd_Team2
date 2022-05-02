#include "stdafx.h"
#include "Obj.h"
#include "ScrollMgr.h"


CObj::CObj() : 
	m_fSpeed(0.f), 
	m_eDir(DIR_END), 
	m_bDead(false), 
	m_targetObj(nullptr),
	m_isGround(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CObj::~CObj() {
}

void CObj::Update_Rect(void) {
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fWidth * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fHeight * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fWidth * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fHeight * 0.5f));

	// Ãæµ¹
	m_tColRect.left = LONG(m_tInfo.fX - (m_tInfo.fColWidth * 0.5f));
	m_tColRect.top = LONG(m_tInfo.fY - (m_tInfo.fColHeight * 0.5f));
	m_tColRect.right = LONG(m_tInfo.fX + (m_tInfo.fColWidth * 0.5f));
	m_tColRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fColHeight * 0.5f));

	int	iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();

	m_tScrollRect.left = m_tRect.left + iScrollX;
	m_tScrollRect.top = m_tRect.top + iScrollY;
	m_tScrollRect.right = m_tRect.right + iScrollX;
	m_tScrollRect.bottom = m_tRect.bottom + iScrollY;
}

void CObj::JumpStart() {
	if (!m_isGround)
		return;

	m_bJump = true;
	m_isGround = false;
	m_fJumpTime = 0.f;
	m_tInfo.fY -= m_tInfo.fHeight;
}

void CObj::Jumping(void) {
	if (!m_bJump)
		return;

	//const float gravity = 9.8f;
	const float gravity = 9.8f;

	m_tInfo.fY -= m_fJumpPower * m_fJumpTime - gravity * m_fJumpTime * m_fJumpTime * 0.5f;
	m_fJumpTime += 0.12f;
}

void CObj::PlatEnter(float _fY) {
	float distY = m_tRect.bottom - _fY;

	if (!m_isGround && sqrtf(distY * distY) < m_tInfo.fHeight) {
		m_isGround = true;
		m_bJump = false;
		m_tInfo.fY = _fY - (m_tInfo.fHeight * 0.5);
	}
	else {
		m_isGround = false;
	}

	Update_Rect();
}

void CObj::Drop(void) {
	if (m_isGround || m_bJump)
		return;

	m_tInfo.fY += FallSpeed;
}