#pragma once
#include "Scene.h"

class GameClient
{
public:
	GameClient();
	~GameClient();

	void Initialize();

	CScene* GetRunningScene() {
		return m_runningScene;
	}

	void LoadScene(CScene* _scene) {
		_scene->Initialize();
		m_runningScene = _scene;
	}

	void SceneLifeCycle();

private:
	void Render();
	void Release();

private:
	HDC	m_hDC;
	CScene* m_runningScene;
};

