#include "stdafx.h"
#include "ObjManager.h"
#include "CollisionMgr.h"

CObjManager* CObjManager::m_pInstance = nullptr;

CObjManager::CObjManager(): m_debug(true) {
}


CObjManager::~CObjManager() {
	Release();
}

void CObjManager::AddObject(OBJID eID, CObj * pObj) {
	if ((eID >= OBJ_END) || (nullptr == pObj))
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjManager::Update(void) {
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);

	for (int i = 0; i < OBJ_END; ++i) {
		for (auto& iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();) {
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult) {
				RemovedToTargetClear(*iter);

				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjManager::Late_Update(void) {
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
}

void CObjManager::Render(HDC hDC) {
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}

	DebugRender(hDC);
}

void CObjManager::DebugRender(HDC hDC) {
	if (!m_debug)
		return;

	TCHAR szBuff[256] = L"";
	swprintf_s(szBuff, L"Monster : %zd", m_ObjList[OBJ_MONSTER].size());
	TextOut(hDC, 200, 200, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"총알 : %zd", m_ObjList[OBJ_BULLET].size());
	TextOut(hDC, 200, 180, szBuff, lstrlen(szBuff));
}

void CObjManager::Release(void) {
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}
}

void CObjManager::RemovedToTargetClear(CObj* _pRemovedObject) {
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
