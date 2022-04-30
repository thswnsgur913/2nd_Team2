#pragma once

#include "Scene.h"
#include "ObjManager.h"
#include "UIManager.h"
#include "ScrollMgr.h"

class GameClient
{
public:
	GameClient();
	~GameClient();

	void Initialize();

	CScene* GetRunningScene() {
		return m_runningScene;
	}

	void ClearManagers();
	void LoadScene(CScene*);

	void SceneLifeCycle();

private:
	void Render();
	void Release();

private:
	HDC	m_hDC;
	CScene* m_runningScene;
};

