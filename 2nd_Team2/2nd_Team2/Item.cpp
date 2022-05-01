#include "stdafx.h"
#include "Player.h"
#include "Item.h"
#include "MainGame.h"

CItem::CItem() {
}


CItem::~CItem() {
}


void CItem::Initialize() {
	m_tInfo.fWidth = 80.f;
	m_tInfo.fHeight = 80.f;

	m_tInfo.fColWidth = 80.f;
	m_tInfo.fColHeight = 80.f;

	m_score = 100;

	Update_Rect();
}

int CItem::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update() {
}

void CItem::Render(HDC hdc) {
	Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CItem::Release() {
}

void CItem::CollisionEnter(CObj* _sour) {
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_sour);
	
	if (!pPlayer)
		return;

	switch (m_type) {
	case ITEM_LIFE:
		// pPlayer->LifeUP();
		CMainGame::Life += 1;
		break;
	case ITEM_SUPER:
		break;
	case ITEM_SCORE:
		CMainGame::Score += m_score;
		break;
	case ITEM_CLOCK:
		CMainGame::DeadTime += g_dwDeltaTime;
		break;
	case ITEM_WEAPON:
		// pPlayer->SwapWeapon(CPlayer::Hammer);
		break;
	}

	m_bDead = true;
}