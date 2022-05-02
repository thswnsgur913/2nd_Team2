#pragma once

#include "Scene.h"

#include "Obj.h"
#include "ObjManager.h"
#include "UIManager.h"
#include "Timer.h"
#include "LinePlat.h"
#include "ScrollMgr.h"
#include "ObjLine.h"

#include "ProgressBar.h"

class CBackUI;
class CPlayer;

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

	void RandomMonster(void);
	void CreateMonster(MONSTERTYPE, float, float);

private:
	void ResourceLoad();

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

	const float StageDeadTime = 100.f;

	// map
	CTimer* m_timer;

	CPlayer* m_player;
	CObj* m_bossMosnter;
	CProgressBar* m_timeProgress;
	CObj* m_monster;
	CBackUI* m_backUI;

	bool m_debug;

	bool m_bMonsterOnOff;

	float m_test;
	DWORD m_dwTime;
};

