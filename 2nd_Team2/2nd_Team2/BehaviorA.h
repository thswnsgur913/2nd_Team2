#pragma once
#include "Monster.h"
class CBehaviorA : // 플레이어 좌표로 돌진 공격
	public CMonster
{
public:
	CBehaviorA();
	CBehaviorA(float _Temp);
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

