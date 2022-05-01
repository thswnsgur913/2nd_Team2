#pragma once
#include "Obj.h"
class CUI : public CObj
{
public:
	CUI();
	~CUI();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void CollisionEnter(CObj*) override;

};

