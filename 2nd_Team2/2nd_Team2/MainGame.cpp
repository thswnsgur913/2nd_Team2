#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

#include "Player.h"

int CMainGame::TotalKillCount = 0;
int CMainGame::KillCount = 0;
int CMainGame::BossCount = BOSS_APPEAR_COUNT;

bool CMainGame::bBoss = false;
long int CMainGame::Score = 0;
int CMainGame::Level = 1;
int CMainGame::PlayTime = 0;

CMainGame::CMainGame():
	m_debug(false)
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	
	m_player = CAbstractFactory<CPlayer>::Create();
	m_ObjList[OBJ_PLAYER].push_back(m_player);

	CPlayer* player = dynamic_cast<CPlayer*>(m_player);

	m_timer = new CTimer;
	m_timer->StartTimer(ENERMY_PER_SECOND, [&]() {
	});
}

void CMainGame::Update(void)
{
	PlayTime += g_dwDeltaTime;
	if (m_ObjList[OBJ_PLAYER].empty()) {
		m_player = nullptr;
	}

	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				RemovedToTargetClear(*iter);
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	if (m_ObjList[OBJ_PLAYER].size() > 0) {
		m_timer->Update();
	}
}

void CMainGame::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto & iter : m_ObjList[i])
			iter->Late_Update();
	}
}

void CMainGame::Render(void)
{
	HBITMAP backBitmap = NULL;
	HBITMAP backBitmapStage = NULL;
	HDC backHDC = CreateCompatibleDC(m_hDC);
	backBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	backBitmapStage = (HBITMAP)SelectObject(backHDC, backBitmap);
	
	BackgroundRender(backHDC);

	for (int i = 0; i < OBJ_END; ++i) {
		for (auto & iter : m_ObjList[i])
			iter->Render(backHDC);
	}

	UIRender(backHDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, backHDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(backHDC, backBitmapStage));
	DeleteDC(backHDC);
}

void CMainGame::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::RemovedToTargetClear(CObj* _pRemovedObject) {
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto* iter : m_ObjList[i]) {
			if (_pRemovedObject == iter) {
				continue;
			}
			
			CObj* currentTarget = (*iter).GetTarget();
			if ((iter->GetTarget()) && _pRemovedObject == (iter->GetTarget())) {
				iter->ClearTarget();
			}
		}
	}

} // 오브젝트가 삭제될때 삭제할 오브젝트를 참조하고있는 오브젝트의 타겟 오브젝트를 nullptr로 바꿔줍니다.

void CMainGame::BackgroundRender(HDC hDC) {
	HBRUSH	brush;
	HGDIOBJ h_old_brush;
	brush = CreateSolidBrush(RGB(0, 0, 105));
	h_old_brush = SelectObject(hDC, brush);
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
}

void CMainGame::UIRender(HDC hDC) {
	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"SCORE : %d", Score);
	TextOut(hDC, WINCX - 100, 50, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"KILL : %d", TotalKillCount);
	TextOut(hDC, 650, 950, szBuff, lstrlen(szBuff));

	//PLAYER level
	swprintf_s(szBuff, L"LEVEL %d", Level);
	TextOutW(hDC, 350, 950, szBuff, lstrlen(szBuff));

	int currentPlayTime = PlayTime;
	int microsecond = currentPlayTime % 10;
	currentPlayTime /= 10;

	int second = currentPlayTime % 60;
	currentPlayTime /= 60;

	int minute = currentPlayTime % 60;

	swprintf_s(szBuff, L"PlayTime: %02d:%02d", minute, second);
	TextOut(hDC, WINCX * 0.5 - 50, 50, szBuff, lstrlen(szBuff));

	if (m_ObjList[OBJ_PLAYER].empty())
	{
		swprintf_s(szBuff, L"GAME OVER");
		TextOut(hDC, static_cast<int>(WINCX * 0.5f) - 50, static_cast<int>(WINCY * 0.5f), szBuff, lstrlen(szBuff));
	}

	DebugRender(hDC);
}

void CMainGame::DebugRender(HDC hDC) {
	if (!m_debug)
		return;
	TCHAR szBuff[256] = L"";
	swprintf_s(szBuff, L"Monster : %zd", m_ObjList[OBJ_MONSTER].size());
	TextOut(hDC, 200, 200, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"총알 : %zd", m_ObjList[OBJ_BULLET].size());
	TextOut(hDC, 200, 180, szBuff, lstrlen(szBuff));
}