#include "stdafx.h"
#include "LinePlat.h"

CLinePlat* CLinePlat::m_pInstance = nullptr;

CLinePlat::CLinePlat()
{
}


CLinePlat::~CLinePlat()
{
	Release();
}

void CLinePlat::Initialize(void)
{	
	Create_Stage();
}

void CLinePlat::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
	{
		iter->Render(hDC);
	}
}

void CLinePlat::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLinePlat::Collision_Line(float & fXX, float * pY)// 여기서 fXX는 플레이어의 x좌표, 
                                                      //*pY는 매개변수 입력을 통해 플레이어의 y좌표가 타게될 라인의 y좌표.
{
	if (m_LineList.empty())
		return false;

	// 플레이어가 라인범위에 있는지 검사.
	CLine* pLine = new CLine;
	
	for (auto& iter : m_LineList)
	{
		if ((fXX >= iter->Get_LINE().tLPoint.fX) && (fXX <= iter->Get_LINE().tRPoint.fX))
		{
			pLine = iter;
		}
	}
	
	if (!pLine)
		return false;

	float fX1 = pLine->Get_LINE().tLPoint.fX;
	float fY1 = pLine->Get_LINE().tLPoint.fY;

	float fX2 = pLine->Get_LINE().tRPoint.fX;
	float fY2 = pLine->Get_LINE().tRPoint.fY;


	*pY = ((fY2 - fY1) / (fX2 - fX1)) * (fXX - fX2) + fY2;

	return true;
}

void CLinePlat::Create_Stage(void)
{
	// 플레이어가 살아있는 동안에 한해서 일정 거리를 달리면
	//새로 추가로 생성하는게 좋을거 같다. 예를들면 if문 추가, for문 추가.
	//bool타입을 추가해서 스테이지를 update에서 추가생성.

	m_LineList.push_back(Create_StartLine()); //게임을 시작시 수평 라인 생성.(게임 스타트)
	//1스테이지: LAND시작.
	Create_Land1();
	//2스테이지: SKY시작.
	Create_Sky();
	//3스테이지: UNDERGROUND시작.
	Create_Underground();
}

CLine* CLinePlat::Create_StartLine(void)
{
	if (m_LineList.empty())// 라인이 생성되지 않았다면 직선라인 출력.(게임시작)
	{
		LINEPOINT LLinePoint[2] =
		{
			{ -100.f,(float)WINCY - 250.f },
			{ 200.f,(float)WINCY - 250.f }
		};
		CLine* m_pLine = new CLine(LLinePoint[0], LLinePoint[1]);

		return m_pLine;
	}
}

void CLinePlat::Create_Land1(void)
{
	LINEPOINT LLinePoint[29] =
	{
		{ 200.f,(float)WINCY - 250.f },
		{ 300.f,(float)WINCY - 250.f },//2번 좌표
		{ 300.f,(float)WINCY - 150.f },
		{ 600.f,(float)WINCY - 150.f },
		{ 1100.f,(float)WINCY - 400.f },
		{ 1400.f,(float)WINCY - 400.f },//6번 좌표
		{ 1400.f,(float)WINCY + 500.f },
		{ 1600.f,(float)WINCY + 500.f },
		{ 1600.f,(float)WINCY - 400.f },
		{ 1800.f,(float)WINCY - 400.f },//10번 좌표
		{ 1800.f,(float)WINCY - 250.f },
		{ 1900.f,(float)WINCY - 150.f },
		{ 2100.f,(float)WINCY - 150.f },
		{ 2100.f,(float)WINCY + 500.f },
		{ 2300.f,(float)WINCY + 500.f },
		{ 2300.f,(float)WINCY - 250.f },//16번 좌표
		{ 2500.f,(float)WINCY - 250.f },
		{ 2600.f,(float)WINCY - 350.f },
		{ 2700.f,(float)WINCY - 350.f },//19번 마지막 좌표,계단 시작좌표.
		                                //1,2스테이지 사이의 계단(upstair)
		{ 2700.f,(float)WINCY - 450.f },//1번 계단.
		{ 2800.f,(float)WINCY - 450.f },
		{ 2800.f,(float)WINCY - 550.f },//2번 계단.
		{ 2900.f,(float)WINCY - 550.f },
		{ 2900.f,(float)WINCY - 650.f },//3번 계단.
		{ 3000.f,(float)WINCY - 650.f },
		{ 3000.f,(float)WINCY - 750.f },//4번 계단.
		{ 3100.f,(float)WINCY - 750.f },
		{ 3100.f,(float)WINCY - 850.f },//5번 계단.
		{ 3200.f,(float)WINCY - 850.f }
	};

	for (int i = 0; i < 28; ++i)
	{
		m_LineList.push_back(new CLine(LLinePoint[i], LLinePoint[i + 1]));
	}
	
}

void CLinePlat::Create_Sky(void)
{
	LINEPOINT LLinePoint[34] =
	{
		{ 3200.f,(float)WINCY - 850.f },
		{ 3500.f,(float)WINCY - 850.f },//2번 좌표
		{ 3500.f,(float)WINCY + 500.f },
		{ 3700.f,(float)WINCY + 500.f },
		{ 3700.f,(float)WINCY - 850.f },
		{ 3900.f,(float)WINCY - 850.f },//6번 좌표
		{ 3900.f,(float)WINCY + 500.f },
		{ 4900.f,(float)WINCY + 500.f },
		{ 4900.f,(float)WINCY - 850.f },
		{ 5100.f,(float)WINCY - 850.f },//10번 좌표
		{ 5100.f,(float)WINCY + 500.f },
		{ 5700.f,(float)WINCY + 500.f },
		{ 5700.f,(float)WINCY - 850.f },//13번 좌표
		{ 6000.f,(float)WINCY - 850.f },//14번 마지막 좌표,계단 시작좌표.
										//2,3스테이지 사이의 계단(upstair)
		{ 6000.f,(float)WINCY - 750.f },//1번 계단.
		{ 6100.f,(float)WINCY - 750.f },
		{ 6100.f,(float)WINCY - 650.f },//2번 계단.
		{ 6200.f,(float)WINCY - 650.f },
		{ 6200.f,(float)WINCY - 550.f },//3번 계단.
		{ 6300.f,(float)WINCY - 550.f },
		{ 6300.f,(float)WINCY - 450.f },//4번 계단.
		{ 6400.f,(float)WINCY - 450.f },
		{ 6400.f,(float)WINCY - 350.f },//5번 계단.
		{ 6500.f,(float)WINCY - 350.f },
		{ 6500.f,(float)WINCY - 250.f },//6번 계단.
		{ 6600.f,(float)WINCY - 250.f },
		{ 6600.f,(float)WINCY - 150.f },//7번 계단.
		{ 6700.f,(float)WINCY - 150.f },
		{ 6700.f,(float)WINCY - 50.f },//8번 계단.
		{ 6800.f,(float)WINCY - 50.f },
		{ 6800.f,(float)WINCY + 50.f },//9번 계단.
		{ 6900.f,(float)WINCY + 50.f },
		{ 6900.f,(float)WINCY + 150.f },//10번 계단.
		{ 7000.f,(float)WINCY + 150.f }
		                               //계단을 아예 직선으로?push_back이 줄어들수있음.

	};

	for (int i = 0; i < 33; ++i)
	{
		m_LineList.push_back(new CLine(LLinePoint[i], LLinePoint[i + 1]));
	}
}

void CLinePlat::Create_Underground(void)
{
	LINEPOINT LLinePoint[34] =
	{
		{ 7000.f,(float)WINCY + 150.f },
		{ 7500.f,(float)WINCY + 150.f },
		{ 7500.f,(float)WINCY + 200.f },
		{ 7800.f,(float)WINCY + 200.f },//4번 좌표
		{ 7800.f,(float)WINCY + 300.f },
		{ 8300.f,(float)WINCY + 300.f },
		{ 8300.f,(float)WINCY + 200.f },//7번 좌표
		{ 8400.f,(float)WINCY + 200.f },
		{ 8700.f,(float)WINCY + 500.f },
		{ 8800.f,(float)WINCY + 500.f },//10번 좌표
		{ 8800.f,(float)WINCY + 1000.f },
		{ 9000.f,(float)WINCY + 1000.f },
		{ 9000.f,(float)WINCY + 500.f },//13번 좌표
		{ 9100.f,(float)WINCY + 500.f },
		{ 9100.f,(float)WINCY + 400.f },
		{ 9300.f,(float)WINCY + 400.f },//16번 좌표
		{ 9300.f,(float)WINCY + 1000.f },
		{ 9500.f,(float)WINCY + 1000.f },
		{ 9500.f,(float)WINCY + 700.f },
		{ 9600.f,(float)WINCY + 700.f },//20번 좌표
		{ 9600.f,(float)WINCY + 1000.f },
		{ 9800.f,(float)WINCY + 1000.f },
		{ 9800.f,(float)WINCY + 700.f },
		{ 9900.f,(float)WINCY + 700.f },//24번 좌표
		{ 9900.f,(float)WINCY + 1000.f },
		{ 10100.f,(float)WINCY + 1000.f },
		{ 10100.f,(float)WINCY + 700.f },
		{ 10200.f,(float)WINCY + 700.f },//28번 좌표
		{ 10200.f,(float)WINCY + 1000.f },
		{ 10400.f,(float)WINCY + 1000.f },
		{ 10400.f,(float)WINCY + 700.f },//31번 좌표
		{ 10600.f,(float)WINCY + 500.f },//32번 마지막 좌표,계단 시작좌표.
		 								 //3,4스테이지 사이의 계단(upstair)
		//{ 6000.f,(float)WINCY - 750.f },//1번 계단.
		//{ 6100.f,(float)WINCY - 750.f },
		//{ 6100.f,(float)WINCY - 650.f },//2번 계단.
		//{ 6200.f,(float)WINCY - 650.f },
		//{ 6200.f,(float)WINCY - 550.f },//3번 계단.
		//{ 6300.f,(float)WINCY - 550.f },
		//{ 6300.f,(float)WINCY - 450.f },//4번 계단.
		//{ 6400.f,(float)WINCY - 450.f },
		//{ 6400.f,(float)WINCY - 350.f },//5번 계단.
		//{ 6500.f,(float)WINCY - 350.f },

	};

	for (int i = 0; i < 28; ++i)
	{
		m_LineList.push_back(new CLine(LLinePoint[i], LLinePoint[i + 1]));
	}
}
