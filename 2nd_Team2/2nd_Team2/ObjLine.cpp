#include "stdafx.h"
#include "ObjLine.h"


CObjLine::CObjLine()
{
}


CObjLine::~CObjLine()
{
}

void CObjLine::Render(HDC hDC)
{
	LINEPOINT LLinePoint[] =
	{
		{ 300.f,(float)WINCY - 250.f },//LAND1_2�� ��ǥ
		{ 300.f,(float)WINCY - 150.f },//3
		{ 1400.f,(float)WINCY - 400.f },//6
		{ 1400.f,(float)WINCY + 500.f },//7
		{ 1600.f,(float)WINCY + 500.f },//8
		{ 1600.f,(float)WINCY - 400.f },//9
		{ 1800.f,(float)WINCY - 400.f },//10
		{ 1800.f,(float)WINCY - 250.f },//11
		{ 2100.f,(float)WINCY - 150.f },//13
		{ 2100.f,(float)WINCY + 500.f },//14
		{ 2300.f,(float)WINCY + 500.f },//15
		{ 2300.f,(float)WINCY - 250.f },//16�� ��ǥ
		{ 2700.f,(float)WINCY - 450.f },//1�� ���.
		{ 2800.f,(float)WINCY - 450.f },
		{ 2800.f,(float)WINCY - 550.f },//2�� ���.
		{ 2900.f,(float)WINCY - 550.f },
		{ 2900.f,(float)WINCY - 650.f },//3�� ���.
		{ 3000.f,(float)WINCY - 650.f },
		{ 3000.f,(float)WINCY - 750.f },//4�� ���.
		{ 3100.f,(float)WINCY - 750.f },
		{ 3100.f,(float)WINCY - 850.f },//5�� ���.
		{ 3200.f,(float)WINCY - 850.f }
	};
	for (int i = 0; 22 > i; ++i)
	{
		if ((1 == i) || (3==i)||(5==i)||(7==i)||(9==i)||(11==i)||(13==i)||(15==i)||(17==i)||(19==i)||(21==i))
		{
			continue;
		}
		else
		{
			MoveToEx(hDC, (int)(LLinePoint[i].fX), (int)(LLinePoint[i].fY), nullptr);
			LineTo(hDC, (int)(LLinePoint[i + 1].fX), (int)(LLinePoint[i + 1].fY));
		}
	}
}
