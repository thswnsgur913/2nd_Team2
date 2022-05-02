#pragma once
#include "Monster.h"
class CBehaviorA : // �÷��̾� ��ǥ�� ���� ����
	public CMonster
{
public:
	CBehaviorA();
	~CBehaviorA();

	// CMonster��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC hDC) override;

	virtual void BehaviorEnter() override;
	virtual void BehaviorExecute() override;
	virtual void BehaviorExit() override;

	virtual bool Jumping() override;
	virtual bool Dir() override;
};
