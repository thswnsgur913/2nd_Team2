#pragma once
#include "Obj.h"
class CFrontUI : public CObj
{
public:
	CFrontUI();
	~CFrontUI();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual	void CollisionEnter(CObj* _sour);

public:

private:

	int m_iFPS;
	DWORD m_dwTime;
};

