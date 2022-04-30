#include "stdafx.h"
#include "GameClient.h"


GameClient::GameClient() {
}


GameClient::~GameClient() {
	Release();
}

void GameClient::Initialize() {
	m_hDC = GetDC(g_hWnd);
}

void GameClient::Render() {
	HBITMAP backBitmap = NULL;
	HBITMAP backBitmapStage = NULL;
	HDC backHDC = CreateCompatibleDC(m_hDC);
	backBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	backBitmapStage = (HBITMAP)SelectObject(backHDC, backBitmap);

	m_runningScene->Render(backHDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, backHDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(backHDC, backBitmapStage));
	DeleteDC(backHDC);
}

void GameClient::SceneLifeCycle() {
	m_runningScene->Update();
	m_runningScene->Late_Update();
	Render();
}

void GameClient::Release() {
	if (m_runningScene)
		Safe_Delete<CScene*>(m_runningScene);
	ReleaseDC(g_hWnd, m_hDC);
}