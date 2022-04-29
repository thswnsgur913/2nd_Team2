#pragma once

#include "Include.h"

#include "Obj.h"
#include "ObjManager.h"
#include "UIManager.h"
#include "Timer.h"

#include "ProgressBar.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void	Initialize(void);
	void	Update(void);
	void	Late_Update(void);
	void	Render(void);
	void	Release(void);

public:
	static int Life;
	static int TotalKillCount;
	static int KillCount;
	static int BossCount;
	static bool bBoss;
	static long Score;
	static int Level;
	static int PlayTime;

private:
	enum monsterType {
		Monster1,
		Monster2,
		Monster3,
		MonsterEnd
	};

	HDC		m_hDC;

	// map
	CTimer* m_timer;

	CObj* m_player;
	CProgressBar* m_timeProgress;

	bool m_debug;

	float m_test;
};

