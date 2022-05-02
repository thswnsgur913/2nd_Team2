#pragma once

#include "UI.h"
#include "Player.h"

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

	void SetWeapon(const CPlayer::WEAPONID _weaponID) { m_weapon = _weaponID; };

private:
	void DrawHammer(HDC);
	void DrawLance(HDC);

private:
	const int GAP;
	CPlayer::WEAPONID m_weapon;


};

