#pragma once

#include "Obj.h"

// MainGame Back UI

class CBackUI : public CObj
{
public:
	CBackUI();
	~CBackUI();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual	void CollisionEnter(CObj* _sour);

};

