#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual	void CollisionEnter(CObj* _sour);

public:

private:
	void KeyInput();
	void Jumping();

private:
	list<CObj*>* m_bulletList; // �Ѿ� ����Ʈ
	list<CObj*>* m_MonsterList; // ���� ����Ʈ

	bool					m_bJump;		// ���� ���� Ȯ��
	float					m_fJumpPower;	// ���� ��
	float					m_fJumpTime;	// ���� �� ���� �ð�
};

