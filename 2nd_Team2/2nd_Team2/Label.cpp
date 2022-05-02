#include "stdafx.h"
#include "Label.h"


CLabel::CLabel() : CLabel(L"") {

}

CLabel::CLabel(const LPCWSTR _text, const LPCWSTR _font):
	m_text(_text),
	m_font(_font),
	m_fontSize(15),
	m_align(ALIGN_MIDDLE),
	m_color(RGB(0, 0, 0)){

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

	SetTextColor(hDC, m_color);
	SetBkMode(hDC, TRANSPARENT);

	oldFont = (HFONT)SelectObject(hDC, textFont);
	tagSIZE size;
	GetTextExtentPoint(hDC, m_text, lstrlen(m_text), &size);
	
	int textHalfWidth = static_cast<int>(size.cx * 0.5f);
	int textHalfHeight = static_cast<int>(size.cy * 0.5f);
	int labelPosX = static_cast<int>(m_tInfo.fX);
	switch (m_align) {
	case ALIGN_LEFT:
		break;
	case ALIGN_RIGHT:
		labelPosX -= size.cx;
		break;
	case ALIGN_MIDDLE:
	default:
		labelPosX -= textHalfWidth;
		break;
	}

	TextOut(hDC, labelPosX, m_tInfo.fY - textHalfHeight, m_text, lstrlen(m_text));

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
