#pragma once
#include "UI.h"

class CLabel : public CUI
{
public:
	CLabel();
	CLabel(const LPCWSTR, const LPCWSTR = TEXT("¸¼Àº °íµñ"));
	virtual ~CLabel();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	CLabel& SetText(const LPCWSTR _text) { m_text = _text; UpdateFont(); return *this; };
	CLabel& SetFontSize(const int _size) { m_fontSize = _size; UpdateFont(); return *this; };
	CLabel& SetFont(const LPCWSTR _fontName) { m_text = _fontName; UpdateFont(); return *this; };

private:
	void UpdateFont();

private:
	const int MAX_LENGTH = 1000;
	LPCWSTR m_text;
	LPCWSTR m_font;
	int m_fontSize;
	LOGFONT m_labelFontInfo;
};

