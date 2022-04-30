#include "stdafx.h"
#include "GameClient.h"

GameClient::GameClient():
	m_pause(false),
	m_fadeAlpha(255),
	m_fadeSpeed(5) {
}


GameClient::~GameClient() {
	Release();
}

void GameClient::Initialize() {
	m_hDC = GetDC(g_hWnd);
}

void GameClient::LoadScene(CScene* _scene) {
	m_reservationLoadScene = _scene;

	if (m_runningScene) {
		m_fadeAlpha = 1;
		m_fadeMode = FADE_OUT;
	}
	else {
		m_fadeAlpha = fadeLimit;
		SceneSwap();
		// 최초 실행
	}
}

void GameClient::Render() {
	HBITMAP backBitmap = NULL;
	HBITMAP backBitmapStage = NULL;
	HDC backHDC = CreateCompatibleDC(m_hDC);
	backBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	backBitmapStage = (HBITMAP)SelectObject(backHDC, backBitmap);

	if (m_runningScene) {
		m_runningScene->Render(backHDC);
	}

	FadeRender(backHDC);

	if (m_fadeAlpha != 0) {
		TCHAR szBuff[32] = L"";

		swprintf_s(szBuff, L"fade : %d", m_fadeAlpha);
		TextOut(backHDC, WINCX - 80, WINCY - 30, szBuff, lstrlen(szBuff));
	}

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, backHDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(backHDC, backBitmapStage));
	DeleteObject(backBitmap);
	DeleteDC(backHDC);
}

void GameClient::SceneLifeCycle() {
	Fading();

	if (!m_pause && m_runningScene) {
		m_runningScene->Update();
		m_runningScene->Late_Update();
	}

	Render();
}

void GameClient::ClearManagers() {
	CObjManager::Instance()->Destroy();
	CUIManager::Instance()->Destroy();
	CScrollMgr::Get_Scroll()->Destroy_Scroll();
}

void GameClient::Release() {
	if (m_runningScene)
		Safe_Delete<CScene*>(m_runningScene);
	
	ReleaseDC(g_hWnd, m_hDC);
}

void GameClient::Fading() {
	if (!m_reservationLoadScene)
		return;

	m_fadeAlpha += m_fadeMode == FADE_OUT ? m_fadeSpeed : -m_fadeSpeed;
	m_fadeAlpha = COLOR_LIMIT(m_fadeAlpha);

	if (m_fadeAlpha >= fadeLimit) {
		m_fadeMode = FADE_IN;
		SceneSwap();
	}

	if (m_fadeAlpha <= 0) {
		FadeEnd();
	}
}

void GameClient::SceneSwap() {
	if (m_runningScene)
		Safe_Delete<CScene*>(m_runningScene);

	ClearManagers();

	m_reservationLoadScene->Initialize();

	m_runningScene = m_reservationLoadScene;
}

void GameClient::FadeEnd() {
	m_reservationLoadScene = nullptr;

	m_pause = false;
}

void GameClient::FadeRender(HDC hdc) {
	HDC fadeHdc = CreateCompatibleDC(hdc);
	HBITMAP fadeBitmap = CreateCompatibleBitmap(fadeHdc, WINCX, WINCY);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(fadeHdc, fadeBitmap);
	
	BLENDFUNCTION bf; 
	bf.AlphaFormat = 0;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = m_fadeAlpha; 
	
	AlphaBlend(hdc, 0, 0, WINCX, WINCY, fadeHdc, 0, 0, WINCX, WINCY, bf);

	DeleteObject(fadeBitmap);
	DeleteObject(oldBitmap);
	DeleteDC(fadeHdc);
}