#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Hammer.h"
#include "Effect.h"
#include "MainGame.h"
#include "Item.h"

CMonster::CMonster():
	baseShotAngle(0),
	m_bAIStart(false),
	m_bRunEffect(false),
	m_bDisplayInfo(false),
	m_effectCount(0),
	m_iScore(0),
	effectDecreasePoint(15),
	m_fTemp(0){
}

CMonster::~CMonster() {
}

int CMonster::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	BehaviorUpdate();

	Drop();

	Update_Rect();

	return OBJ_NOEVENT;
};

void CMonster::Late_Update() {
};


void CMonster::CollisionEnter(CObj* _sour) {

	CBullet* bulletObj = dynamic_cast<CBullet*>(_sour);
	if (bulletObj && bulletObj->GetType() == PLAYER_BULLET) 
	{
		Hit();
		bulletObj->Set_Dead();
	}
}

void CMonster::BehaviorStart(
	CObj* _targetObj 
) {
	m_targetObj = _targetObj;

	m_bAIStart = true;
	behaviorState = Enter;
}

void CMonster::BehaviorUpdate() {
	if (!m_bAIStart || !m_targetObj)
		return;

	switch (behaviorState) {
	case Enter:
		BehaviorEnter();
		break;

	case Execute:
		BehaviorExecute();
		break;

	case Exit:
		BehaviorExit();
		break;
	}
}

bool CMonster::TargetMove() {
	if (targetPosition.x < m_tInfo.fX)
	{
		m_tInfo.fX -= m_fSpeed;
		if(m_fTemp == m_tInfo.fX){ return true; }
		m_fTemp = m_tInfo.fX;
		return false;
	}
	else { return true; }
}

bool CMonster::TargetMoveX() {
	if (targetPosition.x > m_tInfo.fX)
	{
	m_tInfo.fX += m_fSpeed;
	if (m_fTemp == m_tInfo.fX) { return true; }
	m_fTemp = m_tInfo.fX;
	return false;
	}
	else { return true; }
}

void CMonster::Fire(const int _degree, DIRECTION _Dir) {
	CObj* newBullet = CAbstractFactory<CHammer>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, _Dir, 6.5f);

	CBullet* BulletObj = dynamic_cast<CHammer*>(newBullet);
	BulletObj->SetType(MONSTER_BULLET);
	BulletObj->SetDirection(cosf(_degree * RADIAN), sinf(_degree * RADIAN));

	CObjManager::Instance()->AddObject(OBJ_BULLET, newBullet);
}

void CMonster::DisplayInfo(HDC hDC, const int _displayState) {
	if (!m_bDisplayInfo)
		return;

	TCHAR szBuff[256] = L"";
	swprintf_s(szBuff, L"Position : (%f, %f)", m_tInfo.fX, m_tInfo.fY);
	TextOut(hDC, m_tRect.left, m_tRect.top - 20, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"pattern : %d", _displayState);
	TextOut(hDC, m_tRect.left, m_tRect.top - 40, szBuff, lstrlen(szBuff));

	float distX = targetPosition.x - m_tInfo.fX;
	float distY = targetPosition.y - m_tInfo.fY;

	float distance = sqrtf(distX * distX + distY * distY);
	swprintf_s(szBuff, L"distance : %f", distance);
	TextOut(hDC, m_tRect.left, m_tRect.top - 60, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"start TIme : %d, deta Time: %d", g_dwCurrentTime, g_dwDeltaTime);
	TextOut(hDC, m_tRect.left, m_tRect.top - 80, szBuff, lstrlen(szBuff));
}

void CMonster::RunEffect() {
	m_bRunEffect = true;
	m_effectCount = 255;
}

void CMonster::EffectRender() {
	if (!m_bRunEffect)
		return;

	m_effectCount -= effectDecreasePoint;

	if (m_effectCount <= 0) {
		m_effectCount = 0;
		m_bRunEffect = false;
	}
}

void CMonster::Hit() {
	m_iHP -= 10;
	RunEffect();

	if (!m_bDead && m_iHP <= 0) {
		Die();
		CommonDie();
	}
}

void CMonster::CommonDie() {
	CMainGame::KillCount += 1;
	CMainGame::TotalKillCount += 1;
	CMainGame::Score += (m_iScore * CMainGame::Level);

	CObj* newEffect = CAbstractFactory<CEffect>::Create(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CEffect*>(newEffect)->SetEndSize(m_tInfo.fWidth, m_tInfo.fHeight);
	CObjManager::Instance()->AddObject(OBJ_EFFECT, newEffect);

	m_bDead = true;
	m_bAIStart = false;
}

void CMonster::Die() {
	srand((unsigned int)time((nullptr)));

	int iRanDrop = rand() % 100 + 1;
	int iRanItem = rand() % 100 + 1;

	switch (iRanDrop % 3)
	{
	case 1:
	{
		if (0 < iRanItem && 16 >= iRanItem)
		{
			CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_LIFE, { m_tInfo.fX, m_tInfo.fY }));
		}
		else if (16 < iRanItem && 32 >= iRanItem)
		{
			CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { m_tInfo.fX, m_tInfo.fY }));
		}
		else if (32 < iRanItem && 48 >= iRanItem)
		{
			CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEMTYPE::ITEM_WEAPON_LANCE, { m_tInfo.fX, m_tInfo.fY }));
		}
		else if (48 < iRanItem && 64 >= iRanItem)
		{
			CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEMTYPE::ITEM_GOD, { m_tInfo.fX, m_tInfo.fY }));
		}
		else if (64 < iRanItem && 80 >= iRanItem)
		{
			CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEMTYPE::ITEM_WEAPON_HAMMER, { m_tInfo.fX, m_tInfo.fY }));
		}
		else
		{
			CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_CLOCK, { 300.f, 200.f }));
		}
	}
	break;
	}
}