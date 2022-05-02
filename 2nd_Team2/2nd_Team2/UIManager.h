#pragma once

#include "Obj.h"

class CUIManager
{
private:
	CUIManager();
	~CUIManager();

public:
	void AddUI(UIID eID, CObj* pObj);
	int	 Update(void);
	void Late_Update(void);
	void BackRender(HDC hDC);
	void FrontRender(HDC hDC);
	void CUIManager::DebugRender(HDC hDC);
	void Release(void);
	void Clear();

public:
	static CUIManager* Instance(void) {
		if (!m_pInstance) {
			m_pInstance = new CUIManager;
		}

		return m_pInstance;
	}

	static void Destroy(void) {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CUIManager* m_pInstance;
	list<CObj*>	m_UIList[UI_END];
	bool m_debug;
};

