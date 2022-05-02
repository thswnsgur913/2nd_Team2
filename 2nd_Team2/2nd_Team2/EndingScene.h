#pragma once
#include "Scene.h"
class CEndingScene : public CScene
{
public:
	CEndingScene();
	~CEndingScene();

	void Initialize(void) override;
	void Update(void) override;
	void Late_Update(void) override;
	void Render(HDC) override;
	void Release(void) override;

};

