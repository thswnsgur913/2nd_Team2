#pragma once

#include "Scene.h"

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

	INFO m_SelectHighlight;
	Vector2D TargetHighlightPosition;

	int m_currentMenuSelect;
};

