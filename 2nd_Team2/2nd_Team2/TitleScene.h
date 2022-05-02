#pragma once

#include "Scene.h"
#include "Timer.h"

class CLabel;

class CTitleScene : public CScene
{
public:
	CTitleScene();
	virtual ~CTitleScene();

	void Initialize(void) override;
	void Update(void) override;
	void Late_Update(void) override;
	void Render(HDC) override;
	void Release(void) override;

private:
	void RunSeleteMenu();

private:
	enum menu {
		START,
		QUIT,
		MENU_LENGTH
	};

	const int MenubarStartY;
	const int MenuItemHieght;
	const int MenuItemItemGap;

	INFO m_SelectHighlight;
	Vector2D TargetHighlightPosition;

	int m_currentMenuSelect;

	bool m_bSeleted;
	bool m_bBarVisible;

	CTimer* seletedAnimeTimer;
	int m_animeCount;
};

