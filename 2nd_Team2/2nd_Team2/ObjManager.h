#pragma once

#include "Obj.h"
#include "LinePlat.h"

class CObjManager
{
private:
	CObjManager();
	~CObjManager();

public:
	CObj* GetPlayer() { 
		if (m_ObjList[OBJ_PLAYER].empty())
			return nullptr;

		return m_ObjList[OBJ_PLAYER].front(); 
	}

public:
	void AddObject(OBJID eID, CObj* pObj);
	void AddMap(CLinePlat* pObj);

	int	 Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

private:
	void DebugRender(HDC hDC);
	void RemovedToTargetClear(CObj*);

private:
	list<CObj*>	m_ObjList[OBJ_END];
	list<CLinePlat*> m_map;

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

