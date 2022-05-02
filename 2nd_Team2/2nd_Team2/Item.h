#pragma once
#include "Obj.h"
class CItem : public CObj
{
public:
	enum ITEMTYPE {
		ITEM_LIFE,
		ITEM_GOD,
		ITEM_SCORE,
		ITEM_CLOCK,
		ITEM_WEAPON_HAMMER,
		ITEM_WEAPON_LANCE,
		ITEM_END
	};

public:
	CItem();
	~CItem();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void CollisionEnter(CObj* _sour) override;

	void SetType(ITEMTYPE _type) { m_type = _type; }

public:
	static CItem* Create(const ITEMTYPE _type, const Vector2D _position) {
		CItem* newItem = new CItem;
		newItem->Initialize();
		newItem->SetType(_type);
		newItem->Set_pos(_position.x, _position.y);

		return newItem;
	}

private:
	void DrawHammer(HDC);
	void DrawLance(HDC);
	void DrawClock(HDC);
	void DrawApple(HDC);

	void DrawCloud(HDC);

private:
	const int GAP;
	ITEMTYPE m_type;
	int m_score;
};

