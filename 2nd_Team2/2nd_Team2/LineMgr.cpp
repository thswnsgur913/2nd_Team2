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
	//����� ������ �ִٸ� �ҷ�����.

	//���ٸ� �׸���.
	LINEPOINT LLinePoint[4] =
	{
		{ -100.f,(float)WINCY - 200.f },
		{ 250.f,(float)WINCY - 200.f },
		{ 400.f,(float)WINCY - 350.f },
		{ 600.f ,(float)WINCY - 350.f }
	};

	m_LineList.push_back(new CLine(LLinePoint[0], { 250.f,(float)WINCY - 200.f }));
	m_LineList.push_back(new CLine({ 250.f,(float)WINCY - 200.f }, {}));
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

bool CLineMgr::Collision_Line(float & fXX, float * pY)// ���⼭ fXX�� �÷��̾��� x��ǥ, 
                                                      //*pY�� �Ű����� �Է��� ���� �÷��̾��� y��ǥ�� Ÿ�Ե� ������ y��ǥ.
{
	if (m_LineList.empty())
		return false;

	// �÷��̾ ���ι����� �ִ��� �˻�.
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
