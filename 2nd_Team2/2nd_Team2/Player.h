#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "Bullet.h"
#include "Hammer.h"
#include "Lance.h"
#include "Monster.h"
#include "Effect.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "ObjManager.h"
#include "LinePlat.h"
#include "Timer.h"

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

	int	Swap_Weapon(int Weapon) 
	{ 
		if (Weapon == HAMMER)
		{
			m_tPstat.m_Hammer = true;
			m_tPstat.m_Lance = false;
		}

		else if (Weapon == LANCE)
		{
			m_tPstat.m_Lance = true;
			m_tPstat.m_Hammer = false;
		}

		if (m_tPstat.m_Hammer == true)
			return HAMMER;
		else if (m_tPstat.m_Lance == true)
			return LANCE;
		else
			return NO_WEAPON;
	}

	void Set_GodMode(bool GodMode) { m_GodMode = GodMode;}
	void Set_Damage();
	void Set_line(CLinePlat* Line) { m_Line = Line; }
	STAT&	Get_Stat(void) { return m_tPstat; }
	

private:
	void KeyInput();

	void GodMode();

	void OffSet(void);

public:
	enum WEAPONID { NO_WEAPON, HAMMER, LANCE };
	bool m_GodMode;
	//int m_iCount;
	


private:
	const float GodModeSecond = 5.f;
	list<CObj*>* m_bulletList; // �Ѿ� ����Ʈ
	list<CObj*>* m_MonsterList; // ���� ����Ʈ
	CTimer* m_godModeTimer;

	STAT		            m_tPstat; //�÷��̾� �������ͽ�
	CLinePlat*              m_Line;

};

