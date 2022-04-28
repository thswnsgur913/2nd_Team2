#pragma once

#include "Obj.h"

class CObjManager
{
private:
	CObjManager();
	~CObjManager();

public:
	CObj* GetPlayer() { return m_ObjList[OBJ_PLAYER].front(); }

public:
	void AddObject(OBJID eID, CObj* pObj);
	int	 Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

private:
	void DebugRender(HDC hDC);
	void RemovedToTargetClear(CObj*);

private:
	list<CObj*>	m_ObjList[OBJ_END];

public:
	static CObjManager* Instance(void) {
		if (!m_pInstance) {
			m_pInstance = new CObjManager;
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
	static CObjManager* m_pInstance;
	bool m_debug;

};

