#pragma once

#include "Include.h"

#include "Obj.h"
#include "Timer.h"

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

	void	RemovedToTargetClear(CObj*);

private:
	void BackgroundRender(HDC);
	void UIRender(HDC);
	void DebugRender(HDC);

public:
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

	list<CObj*> m_ObjList[OBJ_END];

	TCHAR m_szFPS[64];

	// map
	CTimer* m_timer;

	CObj* m_player;

	bool m_debug;
};

