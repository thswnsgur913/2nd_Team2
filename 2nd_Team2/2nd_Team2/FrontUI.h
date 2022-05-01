#pragma once

#include "Obj.h"
#include "Label.h"

// MainGame Front UI

class CPlayer;

class CFrontUI : public CUI
{
public:
	CFrontUI();
	~CFrontUI();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC) override;
	void Release() override;

public:

private:
	int m_iFPS;
	DWORD m_dwTime;

	CPlayer* m_player;

	CLabel* m_playTimeLabel;
	CLabel* m_gameOverLabel;
};

