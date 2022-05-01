#pragma once
#include "Monster.h"
class CBehaviorBoss :
	public CMonster
{
public:
	CBehaviorBoss();
	~CBehaviorBoss();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC hDC) override;

	virtual void BehaviorEnter() override;
	virtual void BehaviorExecute() override;
	virtual void BehaviorExit() override;

	virtual bool Jumping() override;
	virtual bool Dir() override;

private:
	void RandomPattern();
	void ShootPattern3();
	void ShootPattern4();

private:
	int patternAngle;
};

