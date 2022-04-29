#include "stdafx.h"
#include "UIManager.h"


CUIManager* CUIManager::m_pInstance = nullptr;

CUIManager::CUIManager() : m_debug(true) {
}


CUIManager::~CUIManager() {
	Release();
}

void CUIManager::AddUI(UIID eID, CObj* pObj) {
	if ((eID >= UI_END) || (nullptr == pObj))
		return;

	m_UIList[eID].push_back(pObj);
}

int CUIManager::Update(void) {
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto& iter = m_UIList[i].begin();
			iter != m_UIList[i].end(); ) {
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult) {

				Safe_Delete<CObj*>(*iter);
				iter = m_UIList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CUIManager::Late_Update(void) {
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto& iter : m_UIList[i])
			iter->Late_Update();
	}
}

void CUIManager::FrontRender(HDC hDC) {
	for (auto& iter : m_UIList[UI_FRONT])
		iter->Render(hDC);

	DebugRender(hDC);
}

void CUIManager::BackRender(HDC hDC) {
	for (auto& iter : m_UIList[UI_BACK])
		iter->Render(hDC);
}

void CUIManager::DebugRender(HDC hDC) {
	if (!m_debug)
		return;
}

void CUIManager::Release(void) {
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto& iter : m_UIList[i])
			Safe_Delete<CObj*>(iter);

		m_UIList[i].clear();
	}
}