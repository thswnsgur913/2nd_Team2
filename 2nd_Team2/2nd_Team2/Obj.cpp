#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_eDir(DIR_END), m_bDead(false), m_targetObj(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{

	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fWidth * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fHeight * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fWidth * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fHeight * 0.5f));

	// Ãæµ¹
	m_tColRect.left = LONG(m_tInfo.fX - (m_tInfo.fColWidth * 0.5f));
	m_tColRect.top = LONG(m_tInfo.fY - (m_tInfo.fColHeight * 0.5f));
	m_tColRect.right = LONG(m_tInfo.fX + (m_tInfo.fColWidth * 0.5f));
	m_tColRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fColHeight * 0.5f));
}
