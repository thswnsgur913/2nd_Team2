#pragma once
#include "UI.h"
class CCloud : public CUI
{
public:
	CCloud();
	~CCloud();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void SetSize(float _width) {
		m_tInfo.fWidth = _width;
		Update_Rect();
	}
};

