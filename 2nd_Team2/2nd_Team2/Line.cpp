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
	//��ũ���� �ִٸ� ���⿡�� �ٲٱ�.

	//��ũ�� ����� ������ ��ǥ ��ȭ�� �߰��ؾ���.
	float fScorll_X = CScrollMgr::Get_Scroll()->Get_ScrollX();
	float fScorll_Y = CScrollMgr::Get_Scroll()->Get_ScrollY();

	MoveToEx(hDC, static_cast<int>(m_tInfo.tLPoint.fX + fScorll_X), static_cast<int>(m_tInfo.tLPoint.fY + fScorll_Y), nullptr);
	LineTo(hDC, static_cast<int>(m_tInfo.tRPoint.fX + fScorll_X), static_cast<int>(m_tInfo.tRPoint.fY + fScorll_Y));
}
