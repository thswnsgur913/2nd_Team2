#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public :
	void Set_pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; Update_Rect(); }
	void Set_Dir(DIRECTION _eDir)		{ m_eDir = _eDir; }
	void Set_Speed(float _Speed) { m_fSpeed = _Speed; }
	void Set_Dead(void)					{ m_bDead = true; }
	void SetHP(int _hp)					{ m_iHP = _hp; }
	void SetMaxHP(int _maxHp)			{ m_iMaxHP = _maxHp; }

	int GetHP() { return m_iHP; }
	int GetMaxHP() { return m_iMaxHP; }

	bool GetDead() { return m_bDead; }

	const INFO& Get_Info(void) const { return m_tInfo; }
	const RECT& Get_Rect(void) const { return m_tRect; }
	const RECT& Get_ColRect(void) const { return m_tColRect; }

	void SetTarget(CObj* _targetObj) { m_targetObj = _targetObj; }
	CObj* GetTarget() { return m_targetObj; }
	void ClearTarget() { m_targetObj = nullptr; }

	void PlatEnter(float); // �÷��� �浹
	void SetGround(bool _ground) { m_isGround = _ground; };

public:
	virtual		void	Initialize(void)			PURE;
	virtual		int		Update(void)				PURE;
	virtual		void	Late_Update(void)			PURE;
	virtual		void	Render(HDC hDC)				PURE;
	virtual		void	Release(void)				PURE;
	virtual		void	CollisionEnter(CObj* _sour) PURE;

protected:
	void		Update_Rect(void);

	void Drop(void);
	void Jumping();
	void JumpStart();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	RECT		m_tScrollRect;
	RECT		m_tColRect;
	DIRECTION	m_eDir;
	float		m_fSpeed;
	bool		m_bDead;
	int			m_iMaxHP;
	int			m_iHP;

	CObj* m_targetObj;

	bool m_bJump;		// ���� ���� Ȯ��
	float m_fJumpPower;	// ���� ��
	float m_fJumpTime;	// ���� �� ���� �ð�
	bool m_Dir; //�̵� ���� Ȯ��

	bool m_isGround;
	float m_fDropTime;
};

