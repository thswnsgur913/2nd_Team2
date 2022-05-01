#pragma once
#include "Monster.h"
#include "Timer.h"
#include "LinePlat.h"
class CBehaviorBoss :
	public CMonster
{
public:
	CBehaviorBoss();
	~CBehaviorBoss();

	// CMonster��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC hDC) override;

	virtual void BehaviorEnter() override;
	virtual void BehaviorExecute() override;
	virtual void BehaviorExit() override;

	virtual bool Jumping() override;
	virtual bool Dir() override;

	//void    Set_line(CLinePlat* Line) { m_Line = Line; }

private:
	void RandomPattern();
	void ShootPattern3();
	void ShootPattern4();

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

	//CLinePlat* m_Line;

	int patternAngle;

	int m_iShotCount;
};

