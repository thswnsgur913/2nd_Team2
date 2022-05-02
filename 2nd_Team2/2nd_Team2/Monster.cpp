#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Hammer.h"
#include "Effect.h"
#include "MainGame.h"

CMonster::CMonster():
	baseShotAngle(0),
	m_bAIStart(false),
	m_bRunEffect(false),
	m_bDisplayInfo(false),
	m_effectCount(0),
	m_iScore(0),
	effectDecreasePoint(15){
}

CMonster::~CMonster() {
}

int CMonster::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	BehaviorUpdate();

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
		m_bDead = true;
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
	if (!m_targetObj)
	{
		return true;
	}

	float distX = targetPosition.x - m_tInfo.fX;
	float distY = targetPosition.y - m_tInfo.fY;

	float distance = sqrtf(distX * distX + distY * distY);

	if (distance < 5.f) {
		return true;
	}

	m_tInfo.fX += (distX / distance) * m_fSpeed;
	m_tInfo.fY += (distY / distance) * m_fSpeed;

	return false;
}

bool CMonster::TargetMoveX() {
	float distX = targetPosition.x - m_tInfo.fX;
	float distY = targetPosition.y - m_tInfo.fY;

	float distance = sqrtf(distX * distX + distY * distY);

	if (distance < 5.f) {
		return true;
	}

	m_tInfo.fX += (distX / distance) * m_fSpeed;
	//m_tInfo.fY += (distY / distance) * m_fSpeed;

	return false;
}

bool CMonster::TargetTracking()
{
	if (!m_targetObj)
	{
		return true;
	}

	float distX = m_targetObj->Get_Info().fX - m_tInfo.fX;
	float distY = m_targetObj->Get_Info().fY - m_tInfo.fY;

	float distance = sqrtf(distX * distX + distY * distY);

	if (distance < 5.f) {
		return true;
	}

	m_tInfo.fX += (distX / distance) * m_fSpeed;
	//m_tInfo.fY += (distY / distance) * m_fSpeed;

	return false;
}

void CMonster::Fire(const int _degree, DIRECTION _Dir) {
	/*int iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();*/
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
	m_iHP -= 1;
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
}

void CMonster::LeaveCheck() {
	if (m_tRect.left < -100 || /*m_tRect.right > WINCX + 100 ||*/ m_tRect.top < -100 || m_tRect.bottom > WINCY + 100) {
		m_bDead = true;
	}
} // 떠나기 패턴일때 화면밖을 벗어나는지 체크함

void CMonster::PlatEnter(float _fY) {
	if ((_fY <= m_tInfo.fY) && m_bJump) {
		m_bJump = false;
		m_fJumpTime = 0.f;
		m_tInfo.fY = _fY - PlayerSize * 0.5;
	}
	else {
		if (m_tInfo.fY < _fY - PlayerSize * 0.5)
			Drop();
		else
			m_tInfo.fY = _fY - PlayerSize * 0.5;
	}
}

void CMonster::Drop(void)
{
	m_tInfo.fY += m_fSpeed;
}