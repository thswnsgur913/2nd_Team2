#pragma once
#include "UI.h"

class CProgressBar : public CUI
{
public:
	CProgressBar();
	virtual ~CProgressBar();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void InitProgress(const Vector2D, const Vector2D, const float, const float);
	void SetCurrent(float _value) { 
		m_current = _value >= m_max ? m_max : _value;
		m_rate = m_current / m_max; 
	};

private:
	float m_max;
	float m_current;
	float m_rate;
};

