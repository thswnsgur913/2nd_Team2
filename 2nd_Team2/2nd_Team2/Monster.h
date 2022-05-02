#pragma once
#include "Obj.h"
#include "Timer.h"
#include "LinePlat.h"
#include "ScrollMgr.h"

class CMonster : public CObj
{

public:
	CMonster();
	virtual ~CMonster();
	
	int Update() override;
	void Late_Update() override;

	void SetAppearPosition(const float _x, const float _y) { appearPosition = { _x, _y }; };

	void CollisionEnter(CObj* _sour);
	void BehaviorStart(CObj*);

	int GetScore() { return m_iScore; }

	void Hit(); // 공격당함

protected:
	const int baseShotAngle;

	bool TargetMove();
	bool TargetMoveX();
	void Fire(const int,DIRECTION);
	void DisplayInfo(HDC, const int);
	void RunEffect();
	void EffectRender();

	void BehaviorUpdate();
	virtual void Render(HDC hDC) PURE;

	virtual void BehaviorEnter() PURE;
	virtual void BehaviorExecute() PURE;
	virtual void BehaviorExit() PURE;

	virtual bool Jumping() PURE;
	virtual bool Dir() PURE;

	void CommonDie();
	void Die();

protected:
	enum Behavior {
		Enter,
		Execute,
		Exit
	};

	enum State {
		Create,
		Pattern1,        // 타겟 돌진
		Pattern2,        // 상하 점프
		Pattern3,        // 3연속 공격
		Pattern4,        // 5연속 공격
		Return,          // 돌진 복귀
		Idle
	};


	Vector2D originPosition;
	Vector2D targetPosition;
	Vector2D appearPosition; // 생성후 이동할 위치

	Behavior behaviorState;
	State currentState;

	DWORD m_dwTime;
	CTimer* bossShotTimer;
	//CLinePlat* m_Line;

	float m_fPXpoint;
	float m_fY;
	int m_iShotCount;
	
	bool m_bAIStart;
	bool m_bDisplayInfo;

	int m_effectCount;
	
	int m_iScore;

	float m_fXPoint;

private:
	bool m_bRunEffect;

	int effectDecreasePoint;
};

