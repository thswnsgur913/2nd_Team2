#include "stdafx.h"
#include "BackUI.h"
#include "UIManager.h"
#include "BmpMgr.h"


CBackUI::CBackUI() :
	CloudMAX(17) {
}


CBackUI::~CBackUI()
{
}

void CBackUI::Initialize() {

	//srand(unsigned(time(nullptr)));


	for (int i = 0; i < CloudMAX; ++i) {
		int randomX = rand() % ((int)WINCX + 100) - 100;
		int randomY = rand() % (int)WINCY * 0.4f;
		int ramdomSize = 150;//rand() % (int)150 + 80;
		int randomSpeed = rand() % 3 + 1;

		CCloud* newCloud = new CCloud;
		newCloud->Initialize();
		newCloud->Set_pos(randomX, randomY);
		newCloud->SetSize(ramdomSize);
		newCloud->Set_Speed(randomSpeed * 0.1f);

		m_Clouds.push_back(newCloud);
	}
}

int CBackUI::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	for (auto& cloud : m_Clouds) {
		cloud->Update();
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBackUI::Late_Update() {
}

void CBackUI::Render(HDC hdc) {


	HBRUSH	brush;
	HGDIOBJ h_old_brush;

	int r = COLOR_LIMIT(154 - m_playerDepth);
	int g = COLOR_LIMIT(212 - m_playerDepth);
	int b = COLOR_LIMIT(247 - m_playerDepth);


	brush = CreateSolidBrush(RGB(r, g, b));
	h_old_brush = SelectObject(hdc, brush);
	Rectangle(hdc, 0, 0, WINCX, WINCY);
	SelectObject(hdc, h_old_brush);
	DeleteObject(brush);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Map");
	BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	for (auto& cloud : m_Clouds) {
		cloud->Render(hdc);
	}

}

void CBackUI::Release() {
}

void CBackUI::SetPlayerDepth(int _depth) {
	m_playerDepth = _depth;
}