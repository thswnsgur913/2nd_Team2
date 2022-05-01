#pragma once

#include "UI.h"

class CWeaponBag : public CUI
{
public:
	CWeaponBag();
	virtual ~CWeaponBag();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

