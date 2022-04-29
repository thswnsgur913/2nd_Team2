#pragma once
#include "Monster.h"
#include "Timer.h"
class CBehaviorMonster :
	public CMonster
{
public:
	CBehaviorMonster();
	~CBehaviorMonster();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC hDC) override;


	virtual void BehaviorEnter() override;
	virtual void BehaviorExecute() override;
	virtual void BehaviorExit() override;

private:
	void Jumping();
	void RandomPattern();

private:
	enum State {
		Create,
		Pattern1,        // 타겟 돌진
		Pattern2,        // 상하 점프
		Pattern3,        // 3연속 공격
		Pattern4,        // 5연속 공격
		Return,          // 돌진 복귀
		Idle
	};

	State currentState;

	CTimer* bossShotTimer;

	int patternAngle;

	int m_iShotCount;
};

