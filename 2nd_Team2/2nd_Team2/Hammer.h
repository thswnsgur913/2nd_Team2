#pragma once
#include "obj.h"
#include "Bullet.h"
#include "ScrollMgr.h"

class CHammer:public CBullet
{
public:
	CHammer();
	virtual ~CHammer();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual	void CollisionEnter(CObj* _sour);

/*public:
	BULLET_TYPE GetType() const;
	void SetType(BULLET_TYPE eType);
	void SetDirection(float _x, float _y) { m_tDir.fX = _x, m_tDir.fY = _y; };*/

public:
	virtual void Throw();

private:
	/*INFO m_tDir;
	BULLET_TYPE m_eBulletType;*/

	bool					m_bThrow;		// ������ ���� Ȯ��
	float					m_fThrowPower;	// ������ ��
	float					m_fThrowTime;	// ������ �� ���� �ð�
};

