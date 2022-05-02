#pragma once
#include "Monster.h"
class CBehaviorC : // 플레이어 방향으로 투척 공격
	public CMonster
{
public:
	CBehaviorC();
	CBehaviorC(float _Temp);
	~CBehaviorC();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC hDC) override;

	virtual void BehaviorEnter() override;
	virtual void BehaviorExecute() override;
	virtual void BehaviorExit() override;

	virtual bool Jumping() override;
	virtual bool Dir() override;

	void Shoot();
};

