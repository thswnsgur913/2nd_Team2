#pragma once

#include "UI.h"
#include "Cloud.h"

// MainGame Back UI

class CBackUI : public CUI
{
public:

	CBackUI();
	~CBackUI();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void SetPlayerDepth(int); // ��׶��� ���� ������ ���� ����

private:
	const int CloudMAX;
	int m_playerDepth;

	list<CCloud*> m_Clouds;
};

