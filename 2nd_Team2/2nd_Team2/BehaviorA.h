#pragma once
#include "Monster.h"
class CBehaviorA :
	public CMonster
{
public:
	CBehaviorA();
	~CBehaviorA();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC hDC) override;

	virtual void BehaviorEnter() override;
	virtual void BehaviorExecute() override;
	virtual void BehaviorExit() override;

	virtual bool Jumping() override;
	virtual bool Dir() override;
};

