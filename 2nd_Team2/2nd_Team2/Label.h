#pragma once
#include "UI.h"

class CLabel : public CUI
{
public:
	CLabel();
	CLabel(const LPCWSTR _text);
	virtual ~CLabel();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void SetText(LPCWSTR _text) { m_text = _text; };

private:
	const int MAX_LENGTH = 1000;
	LPCWSTR m_text;
};

