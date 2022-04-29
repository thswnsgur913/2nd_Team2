#include "stdafx.h"
#include "LineMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	//저장된 라인이 있다면 불러오기.

	//없다면 그리기.
	//일단은 시작하는 지형 그림.(추후에 좌표를 넘기는 방식으로 여러 패턴의 라인을 연결 시키고 싶음.)
	LINEPOINT LLinePoint[4] =
	{
		{ -100.f,(float)WINCY - 200.f },
		{ 250.f,(float)WINCY - 200.f },
		{ 400.f,(float)WINCY - 350.f },
		{ 600.f ,(float)WINCY - 350.f }
	};

	m_LineList.push_back(new CLine(LLinePoint[0], LLinePoint[1]));
	m_LineList.push_back(new CLine(LLinePoint[1],LLinePoint[2]));
	m_LineList.push_back(new CLine(LLinePoint[2], LLinePoint[3]));

}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
	{
		iter->Render(hDC);
	}
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float & fXX, float * pY)// 여기서 fXX는 플레이어의 x좌표, 
                                                      //*pY는 매개변수 입력을 통해 플레이어의 y좌표가 타게될 라인의 y좌표.
{
	if (m_LineList.empty())
		return false;

	// 플레이어가 라인범위에 있는지 검사.
	CLine* pLine = new CLine;

	for (auto& iter : m_LineList)
	{
		if ((fXX >= iter->Get_LINE().tLPoint.fX) && (fXX <= iter->Get_LINE().tRPoint.fX))
		{
			pLine = iter;
		}
	}

	if (!pLine)
		return false;

	float fX1 = pLine->Get_LINE().tLPoint.fX;
	float fY1 = pLine->Get_LINE().tLPoint.fY;

	float fX2 = pLine->Get_LINE().tRPoint.fX;
	float fY2 = pLine->Get_LINE().tRPoint.fY;


	*pY = ((fY2 - fY1) / (fX2 - fX1)) * (fXX - fX2) + fY2;

	return true;
}
