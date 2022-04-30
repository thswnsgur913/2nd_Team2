#pragma once
#include "Include.h"
#include "ScrollMgr.h"

class CLine
{
public:
	CLine();
	CLine(LINE m_tLine);
	CLine(LINEPOINT m_tLPOINT, LINEPOINT m_tRPOINT);
	~CLine();

public:
	const LINE& Get_LINE(void) { return m_tInfo; }

	void Render(HDC hDC);

private:
	LINE    m_tInfo;
};

