#include "stdafx.h"
#include "LinePlat.h"
#include "Player.h"

CLinePlat::CLinePlat()
{
}

CLinePlat::CLinePlat(vector<LINEPOINT> _linePoints) {
	for (int index = 0; index < _linePoints.size() - 1; ++index) {
		m_LineList.push_back(new CLine(_linePoints[index], _linePoints[index + 1]));
	}
}


CLinePlat::~CLinePlat()
{
	Release();
}

void CLinePlat::Initialize(void) {

}

int CLinePlat::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CLinePlat::Late_Update() {

}

void CLinePlat::CollisionEnter(CObj* _sour) {

}

void CLinePlat::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
	{
		iter->Render(hDC);
	}
}

void CLinePlat::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLinePlat::Collision_Line(CObj* _sour)//플레이어, 몬스터입력가능.
{
	float fXX = _sour->Get_Info().fX;

	if (m_LineList.empty())
		return false;

	// 플레이어가 라인범위에 있는지 검사.
	CLine* pLine = nullptr;
	float fY = 0.f;
	float pY = 0.f;
	
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

	if ((fX1 == fX2)&&(_sour->Get_Info().fY > fY1))//&&(fY1 < fY2)
	{
		dynamic_cast<CPlayer*>(_sour)->PlatEnterX(fX1);
		return false;
	}
	/*else if ((fX1 == fX2) && (_sour->Get_Info().fY > fY2) && (fY1 < fY2))
	{
		dynamic_cast<CPlayer*>(_sour)->PlatEnterX2(fX1);
		return false;
	}*/
	
	pY = ((fY2 - fY1) / (fX2 - fX1)) * (fXX - fX2) + fY2;

	if (dynamic_cast<CPlayer*>(_sour)) {
		dynamic_cast<CPlayer*>(_sour)->PlatEnter(pY);
	}
	
	return true;
}