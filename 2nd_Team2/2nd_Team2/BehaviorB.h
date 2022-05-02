#pragma once
#include "Monster.h"
class CBehaviorB : // 제자리에서 점프
	public CMonster
{
public:
	CBehaviorB();
	CBehaviorB(float _Temp);
	~CBehaviorB();

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

