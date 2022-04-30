#pragma once

#include "Scene.h"

class CTitleScene : public CScene
{
public:
	CTitleScene();
	virtual ~CTitleScene();

	virtual void Initialize(void) PURE;
	virtual void Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC) PURE;
	virtual void Release(void) PURE;
};

