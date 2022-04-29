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
	MoveToEx(hDC, m_tInfo.tLPoint.fX, m_tInfo.tLPoint.fY, nullptr);
	LineTo(hDC, m_tInfo.tRPoint.fX, m_tInfo.tRPoint.fY);
}
