#pragma once

#include "Obj.h"

class CWeaponBag : public CObj
{
public:
	CWeaponBag();
	virtual ~CWeaponBag();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void CollisionEnter(CObj* _sour) override;

};

