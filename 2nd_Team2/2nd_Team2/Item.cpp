#include "stdafx.h"
#include "Player.h"
#include "Item.h"
#include "MainGame.h"
#include "BmpMgr.h"

CItem::CItem():
	GAP(10) {
}


CItem::~CItem() {
}


void CItem::Initialize() {
	m_tInfo.fWidth = 40.f;
	m_tInfo.fHeight = 40.f;

	m_tInfo.fColWidth = 40.f;
	m_tInfo.fColHeight = 40.f;

	m_score = 100;

	m_fSpeed = 10.f;

	Update_Rect();
}

int CItem::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	Drop();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update() {
}

void CItem::Render(HDC hdc) {
	int	iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();


	//Rectangle(hdc, m_tScrollRect.left, m_tScrollRect.top, m_tScrollRect.right, m_tScrollRect.bottom);
	//Rectangle(hdc, m_tScrollRect.left + GAP, m_tScrollRect.top + GAP, m_tScrollRect.right - GAP, m_tScrollRect.bottom - GAP);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ITEM_LIFE");;

	switch (m_type) {
	case ITEM_LIFE: 
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ITEM_LIFE");
		break;

	case ITEM_GOD:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ITEM_GOD");
		break;

	case ITEM_SCORE:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ITEM_SCORE");
		break;

	case ITEM_CLOCK:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ITEM_CLOCK");
		break;

	case ITEM_WEAPON_HAMMER:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ITEM_WEAPON_HAMMER");
		break;

	case ITEM_WEAPON_LANCE:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ITEM_WEAPON_LANCE");
		break;
	}

	GdiTransparentBlt(hdc,
		int(m_tScrollRect.left),
		int(m_tScrollRect.top),
		int(m_tInfo.fWidth),
		int(m_tInfo.fHeight),
		hMemDC,
		0,
		0,
		(int)m_tInfo.fWidth,
		(int)m_tInfo.fHeight,
		RGB(255, 255, 255));
}

void CItem::Release() {
}

void CItem::CollisionEnter(CObj* _sour) {
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_sour);
	
	if (!pPlayer)
		return;

	switch (m_type) {
	case ITEM_LIFE:
		CMainGame::Life += 1;
		break;

	case ITEM_GOD:
		pPlayer->GodMode();
		break;

	case ITEM_SCORE:
		CMainGame::Score += m_score;
		break;

	case ITEM_CLOCK:
		CMainGame::DeadTime += g_dwDeltaTime;
		break;

	case ITEM_WEAPON_HAMMER:
		pPlayer->Swap_Weapon(CPlayer::WEAPONID::HAMMER);
		break;

	case ITEM_WEAPON_LANCE:
		pPlayer->Swap_Weapon(CPlayer::WEAPONID::LANCE);
		break;
	}

	m_bDead = true;
}

void CItem::DrawHammer(HDC hdc) {
	HBRUSH brush;
	HGDIOBJ oldBrush;

	brush = CreateSolidBrush(RGB(150, 75, 0));
	oldBrush = SelectObject(hdc, brush);

	Rectangle(hdc, m_tScrollRect.left + GAP + 35, m_tScrollRect.top + GAP + 5, m_tScrollRect.right - GAP - 35, m_tScrollRect.bottom - GAP - 5);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = SelectObject(hdc, brush);

	Rectangle(hdc, m_tScrollRect.left + GAP + 5, m_tScrollRect.top + GAP + 10, m_tScrollRect.right - GAP - 5, m_tScrollRect.top + GAP + 30);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

void CItem::DrawLance(HDC hdc) {
	HBRUSH brush;
	HGDIOBJ oldBrush;

	brush = CreateSolidBrush(RGB(150, 75, 0));
	oldBrush = SelectObject(hdc, brush);

	Rectangle(hdc, m_tScrollRect.left + GAP + 35, m_tScrollRect.top + GAP + 5, m_tScrollRect.right - GAP - 35, m_tScrollRect.bottom - GAP - 5);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

void CItem::DrawClock(HDC hdc) {
	Ellipse(hdc, m_tRect.left + GAP, m_tRect.top + GAP, m_tRect.right - GAP, m_tRect.bottom - GAP);
	
	MoveToEx(hdc, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hdc, m_tInfo.fX, m_tRect.top + GAP + 10);

	MoveToEx(hdc, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hdc, m_tRect.right - GAP + 10, m_tInfo.fY);
}

void CItem::DrawApple(HDC hdc) {
	HBRUSH brush;
	HGDIOBJ oldBrush;

	brush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = SelectObject(hdc, brush);

	Ellipse(hdc, m_tScrollRect.left + GAP, m_tScrollRect.top + GAP, m_tScrollRect.right - GAP, m_tScrollRect.bottom - GAP);
	
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

void CItem::DrawCloud(HDC hdc) {
	float centerX = m_tInfo.fX;
	float centerY = m_tInfo.fY;

	Ellipse(hdc, m_tRect.left + GAP, m_tRect.top + GAP, m_tRect.right - GAP, m_tRect.bottom - GAP);
	Ellipse(hdc, m_tRect.left + GAP, m_tRect.top + GAP, m_tRect.right - GAP, m_tRect.bottom - GAP);
	Ellipse(hdc, m_tRect.left + GAP, m_tRect.top + GAP, m_tRect.right - GAP, m_tRect.bottom - GAP);

}