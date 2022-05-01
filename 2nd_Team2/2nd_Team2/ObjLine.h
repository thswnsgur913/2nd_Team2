#pragma once
#include "Obj.h"
#include "Include.h"

class CObjLine :
	public CObj
{
public:
	CObjLine();
	virtual ~CObjLine();

public:
	//virtual		void	Initialize(void);
	//virtual		int		Update(void);
	//virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	//virtual		void	Release(void);
	//virtual		void	CollisionEnter(CObj* _sour);

public:
	////CObj* Create()
	//{
	//	//CObj* pLine = new CObjLine;
	//	
	//	//return pLine;
	//}
};

