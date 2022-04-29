#pragma once
#include "Monster.h"
#include "Timer.h"
class CBehaviorMonster :
	public CMonster
{
public:
	CBehaviorMonster();
	~CBehaviorMonster();

	// CMonster��(��) ���� ��ӵ�
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
		Pattern1,        // Ÿ�� ����
		Pattern2,        // ���� ����
		Pattern3,        // 3���� ����
		Pattern4,        // 5���� ����
		Return,          // ���� ����
		Idle
	};

	State currentState;

	CTimer* bossShotTimer;

	int patternAngle;

	int m_iShotCount;
};

