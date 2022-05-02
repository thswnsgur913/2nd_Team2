#pragma once
#include "Obj.h"
#include "Include.h"
#include "ScrollMgr.h"
#include "Player.h"

class CObjLine :
	public CObj
{
public:
	CObjLine();
	CObjLine(LINEPOINT _LeftP,LINEPOINT _RightP);
	virtual ~CObjLine();

public:
	void	Initialize(void) override;
	int		Update(void) override;
	void	Late_Update(void) override;
	void	Render(HDC hDC) override;
	void	Release(void) override;
	void	CollisionEnter(CObj* _sour) override;

public:
	void Collision_OBJLINE(CObj* pObj);

	static CObjLine* Create(LINEPOINT _LeftP, LINEPOINT _RightP)
	{
		CObjLine* Obstacle_Line = new CObjLine(_LeftP,_RightP);
		Obstacle_Line->Initialize();

		return Obstacle_Line;
	}

private:
	LINEPOINT POINT1;
	LINEPOINT POINT2;
	bool m_bOnLeft; //플레이어의 원래 위치.(좌우)
	bool m_bOnRight;
};

