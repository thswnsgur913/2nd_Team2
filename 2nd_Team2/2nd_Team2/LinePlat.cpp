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

	pointSize = static_cast<int>(_linePoints.size() - 1);
	m_DrawLineList = new POINT[_linePoints.size()];
	m_ScrollDrawLineList = new POINT[_linePoints.size()];

	for (int index = 0; index < pointSize; ++index) {
		m_DrawLineList[index] = { static_cast<long>(_linePoints[index].fX), static_cast<long>(_linePoints[index].fY) };
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
	// drawLineList
	for (auto& iter : m_LineList) {
		iter->Render(hDC);
	}

	float fScorllX = CScrollMgr::Get_Scroll()->Get_ScrollX();
	float fScorllY = CScrollMgr::Get_Scroll()->Get_ScrollY();

	for (int index = 0; index < pointSize; ++index) {
		m_ScrollDrawLineList[index] = { static_cast<long>(m_DrawLineList[index].x + fScorllX), static_cast<long>(m_DrawLineList[index].y + fScorllY) };
	}

	HBRUSH brush = CreateSolidBrush(RGB(171, 113, 80));
	HGDIOBJ oldBrush = SelectObject(hDC, brush);

	Polygon(hDC, m_ScrollDrawLineList, static_cast<int>(m_LineList.size())); // 좌표의 수.

	SelectObject(hDC, oldBrush);
	DeleteObject(brush);

}

void CLinePlat::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLinePlat::Collision_Line(CObj* _sour)//플레이어, 몬스터입력가능.
{
	float fXX = _sour->Get_Info().fX;
	float fYY = static_cast<float>(_sour->Get_Rect().bottom);

	if (m_LineList.empty())
		return false;

	// 플레이어가 라인범위에 있는지 검사.
	CLine* pLine = nullptr;
	float fY = 0.f;
	float pY = 0.f;
	
	for (auto& iter : m_LineList) {
		float lPointX = iter->Get_LINE().tLPoint.fX;
		float rPointX = iter->Get_LINE().tRPoint.fX;

		if ((fXX >= lPointX) && (fXX <= rPointX) && lPointX != rPointX) {
			pLine = iter;
		}
	}
	
	if (!pLine)
		return false;

	float fXXL = static_cast<float>(_sour->Get_Rect().left);
	float fXXR = static_cast<float>(_sour->Get_Rect().right);

	float fX1 = pLine->Get_LINE().tLPoint.fX;
	float fY1 = pLine->Get_LINE().tLPoint.fY;

	float fX2 = pLine->Get_LINE().tRPoint.fX;
	float fY2 = pLine->Get_LINE().tRPoint.fY;
		
	float slope = (fY2 - fY1) / (fX2 - fX1);

	pY = slope * (fXX - fX2) + fY2;

	float topPoint = fY1 > fY2 ? fY2 : fY1;

	float distY = fYY - pY;


	_sour->PlatEnter(pY);
	//if (fCY > fHeight) {
	//}

	if (dynamic_cast<CPlayer*>(_sour)) {
		dynamic_cast<CPlayer*>(_sour)->SetStartPoint({ fX1 + 100.f , pY - 100.f });
	}



	return true;
}