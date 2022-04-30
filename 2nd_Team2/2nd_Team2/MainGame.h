#pragma once

#include "Scene.h"

#include "Obj.h"
#include "ObjManager.h"
#include "UIManager.h"
#include "Timer.h"
#include "LinePlat.h"
#include "ScrollMgr.h"

#include "ProgressBar.h"


class CMainGame : public CScene {
public:
	CMainGame();
	virtual ~CMainGame();

public:
	void Initialize(void) override;
	void Update(void) override;
	void Late_Update(void) override;
	void Render(HDC) override;
	void Release(void) override;

public:
	static int Life;
	static int TotalKillCount;
	static int KillCount;
	static int BossCount;
	static bool bBoss;
	static long Score;
	static int Level;
	static int PlayTime;
	static float DeadTime;

private:
	enum monsterType {
		Monster1,
		Monster2,
		Monster3,
		MonsterEnd
	};

	// map
	CTimer* m_timer;

	CObj* m_player;
	CProgressBar* m_timeProgress;

	bool m_debug;

	float m_test;

	list<CLinePlat*> m_map;
};

