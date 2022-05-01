#include "stdafx.h"
#include "Label.h"


CLabel::CLabel() {

}

CLabel::CLabel(const LPCWSTR _text, const LPCWSTR _font):
	m_text(_text),
	m_font(_font),
	m_fontSize(15) {

	UpdateFont();
}

CLabel::~CLabel() {

}

void CLabel::Initialize() {

};

int CLabel::Update() {
	return 0;
};

void CLabel::Late_Update() {

};

void CLabel::Render(HDC hDC) {
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);

	oldFont = (HFONT)SelectObject(hDC, textFont);
	tagSIZE size;
	GetTextExtentPoint(hDC, m_text, lstrlen(m_text), &size);
	int textHalfWidth = static_cast<int>(size.cx * 0.5f);

	TextOut(hDC, static_cast<int>(m_tInfo.fX) - textHalfWidth, m_tInfo.fY, m_text, lstrlen(m_text));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);
};

void CLabel::Release() {

};

void CLabel::UpdateFont() {
	memset(&m_labelFontInfo, 0, sizeof(m_labelFontInfo));
	m_labelFontInfo.lfHeight = m_fontSize;
	m_labelFontInfo.lfWeight = FW_BOLD;
	lstrcpy(m_labelFontInfo.lfFaceName, m_font);
}
