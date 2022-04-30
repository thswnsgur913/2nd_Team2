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
	void SceneSwap();

	void SceneLifeCycle();

private:
	void Render();
	void Release();

	void Fading();
	void FadeEnd();
	void FadeRender(HDC);

private:
	const int fadeLimit = 255;
	const int m_fadeSpeed;

	enum fade {
		FADE_IN,
		FADE_OUT,
		FADE_LENGTH
	};

	int m_fadeAlpha; // ∫“≈ı∏Ì 255
	fade m_fadeMode;

	HDC	m_hDC;
	CScene* m_runningScene;
	bool m_pause;

	CScene* m_reservationLoadScene;
};

