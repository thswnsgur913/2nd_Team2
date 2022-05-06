#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(LINE m_tLine)
	:m_tInfo(m_tLine)
{
}

CLine::CLine(LINEPOINT m_tLPOINT, LINEPOINT m_tRPOINT)
	:m_tInfo(m_tLPOINT,m_tRPOINT)
{
}


CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	//스크롤이 있다면 여기에서 바꾸기.

	//스크롤 존재시 상응한 좌표 변화를 추가해야함.
	float fScorll_X = CScrollMgr::Get_Scroll()->Get_ScrollX();
	float fScorll_Y = CScrollMgr::Get_Scroll()->Get_ScrollY();

	MoveToEx(hDC, static_cast<int>(m_tInfo.tLPoint.fX + fScorll_X), static_cast<int>(m_tInfo.tLPoint.fY + fScorll_Y), nullptr);
	LineTo(hDC, static_cast<int>(m_tInfo.tRPoint.fX + fScorll_X), static_cast<int>(m_tInfo.tRPoint.fY + fScorll_Y));
}
