#include "stdafx.h"
#include "Label.h"


CLabel::CLabel() {

}

CLabel::CLabel(const LPCWSTR _text):
	m_text(_text) {

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
	LOGFONT titleFont;
	memset(&titleFont, 0, sizeof(titleFont));
	titleFont.lfHeight = 150; // see PS
	titleFont.lfWeight = FW_BOLD;
	lstrcpy(titleFont.lfFaceName, TEXT("Broadway"));
	textFont = CreateFontIndirect(&titleFont);

	oldFont = (HFONT)SelectObject(hDC, textFont);
	tagSIZE size;
	GetTextExtentPoint(hDC, m_text, lstrlen(m_text), &size);
	int textHalfWidth = static_cast<int>(size.cx * 0.5f);

	TextOut(hDC, m_tInfo.fX - textHalfWidth, m_tInfo.fY, m_text, lstrlen(m_text));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);
};

void CLabel::Release() {

};
