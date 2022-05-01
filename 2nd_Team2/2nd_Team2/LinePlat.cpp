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

bool CLinePlat::Collision_Line(float & fXX, float * pY)// ���⼭ fXX�� �÷��̾��� x��ǥ, 
                                                      //*pY�� �Ű����� �Է��� ���� �÷��̾��� y��ǥ�� Ÿ�Ե� ������ y��ǥ.
{
	if (m_LineList.empty())
		return false;

	// �÷��̾ ���ι����� �ִ��� �˻�.
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
	// �÷��̾ ����ִ� ���ȿ� ���ؼ� ���� �Ÿ��� �޸���
	//���� �߰��� �����ϴ°� ������ ����. ������� if�� �߰�, for�� �߰�.
	//boolŸ���� �߰��ؼ� ���������� update���� �߰�����.

	m_LineList.push_back(Create_StartLine()); //������ ���۽� ���� ���� ����.(���� ��ŸƮ)
	//1��������: LAND����.
	Create_Land1();
	//2��������: SKY����.
	Create_Sky();
	//3��������: UNDERGROUND����.
	Create_Underground();
}

CLine* CLinePlat::Create_StartLine(void)
{
	if (m_LineList.empty())// ������ �������� �ʾҴٸ� �������� ���.(���ӽ���)
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
		{ 300.f,(float)WINCY - 250.f },//2�� ��ǥ
		{ 300.f,(float)WINCY - 150.f },
		{ 600.f,(float)WINCY - 150.f },
		{ 1100.f,(float)WINCY - 400.f },
		{ 1400.f,(float)WINCY - 400.f },//6�� ��ǥ
		{ 1400.f,(float)WINCY + 500.f },
		{ 1600.f,(float)WINCY + 500.f },
		{ 1600.f,(float)WINCY - 400.f },
		{ 1800.f,(float)WINCY - 400.f },//10�� ��ǥ
		{ 1800.f,(float)WINCY - 250.f },
		{ 1900.f,(float)WINCY - 150.f },
		{ 2100.f,(float)WINCY - 150.f },
		{ 2100.f,(float)WINCY + 500.f },
		{ 2300.f,(float)WINCY + 500.f },
		{ 2300.f,(float)WINCY - 250.f },//16�� ��ǥ
		{ 2500.f,(float)WINCY - 250.f },
		{ 2600.f,(float)WINCY - 350.f },
		{ 2700.f,(float)WINCY - 350.f },//19�� ������ ��ǥ,��� ������ǥ.
		                                //1,2�������� ������ ���(upstair)
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
		{ 3500.f,(float)WINCY - 850.f },//2�� ��ǥ
		{ 3500.f,(float)WINCY + 500.f },
		{ 3700.f,(float)WINCY + 500.f },
		{ 3700.f,(float)WINCY - 850.f },
		{ 3900.f,(float)WINCY - 850.f },//6�� ��ǥ
		{ 3900.f,(float)WINCY + 500.f },
		{ 4900.f,(float)WINCY + 500.f },
		{ 4900.f,(float)WINCY - 850.f },
		{ 5100.f,(float)WINCY - 850.f },//10�� ��ǥ
		{ 5100.f,(float)WINCY + 500.f },
		{ 5700.f,(float)WINCY + 500.f },
		{ 5700.f,(float)WINCY - 850.f },//13�� ��ǥ
		{ 6000.f,(float)WINCY - 850.f },//14�� ������ ��ǥ,��� ������ǥ.
										//2,3�������� ������ ���(upstair)
		{ 6000.f,(float)WINCY - 750.f },//1�� ���.
		{ 6100.f,(float)WINCY - 750.f },
		{ 6100.f,(float)WINCY - 650.f },//2�� ���.
		{ 6200.f,(float)WINCY - 650.f },
		{ 6200.f,(float)WINCY - 550.f },//3�� ���.
		{ 6300.f,(float)WINCY - 550.f },
		{ 6300.f,(float)WINCY - 450.f },//4�� ���.
		{ 6400.f,(float)WINCY - 450.f },
		{ 6400.f,(float)WINCY - 350.f },//5�� ���.
		{ 6500.f,(float)WINCY - 350.f },
		{ 6500.f,(float)WINCY - 250.f },//6�� ���.
		{ 6600.f,(float)WINCY - 250.f },
		{ 6600.f,(float)WINCY - 150.f },//7�� ���.
		{ 6700.f,(float)WINCY - 150.f },
		{ 6700.f,(float)WINCY - 50.f },//8�� ���.
		{ 6800.f,(float)WINCY - 50.f },
		{ 6800.f,(float)WINCY + 50.f },//9�� ���.
		{ 6900.f,(float)WINCY + 50.f },
		{ 6900.f,(float)WINCY + 150.f },//10�� ���.
		{ 7000.f,(float)WINCY + 150.f }
		                               //����� �ƿ� ��������?push_back�� �پ�������.

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
		{ 7800.f,(float)WINCY + 200.f },//4�� ��ǥ
		{ 7800.f,(float)WINCY + 300.f },
		{ 8300.f,(float)WINCY + 300.f },
		{ 8300.f,(float)WINCY + 200.f },//7�� ��ǥ
		{ 8400.f,(float)WINCY + 200.f },
		{ 8700.f,(float)WINCY + 500.f },
		{ 8800.f,(float)WINCY + 500.f },//10�� ��ǥ
		{ 8800.f,(float)WINCY + 1000.f },
		{ 9000.f,(float)WINCY + 1000.f },
		{ 9000.f,(float)WINCY + 500.f },//13�� ��ǥ
		{ 9100.f,(float)WINCY + 500.f },
		{ 9100.f,(float)WINCY + 400.f },
		{ 9300.f,(float)WINCY + 400.f },//16�� ��ǥ
		{ 9300.f,(float)WINCY + 1000.f },
		{ 9500.f,(float)WINCY + 1000.f },
		{ 9500.f,(float)WINCY + 700.f },
		{ 9600.f,(float)WINCY + 700.f },//20�� ��ǥ
		{ 9600.f,(float)WINCY + 1000.f },
		{ 9800.f,(float)WINCY + 1000.f },
		{ 9800.f,(float)WINCY + 700.f },
		{ 9900.f,(float)WINCY + 700.f },//24�� ��ǥ
		{ 9900.f,(float)WINCY + 1000.f },
		{ 10100.f,(float)WINCY + 1000.f },
		{ 10100.f,(float)WINCY + 700.f },
		{ 10200.f,(float)WINCY + 700.f },//28�� ��ǥ
		{ 10200.f,(float)WINCY + 1000.f },
		{ 10400.f,(float)WINCY + 1000.f },
		{ 10400.f,(float)WINCY + 700.f },//31�� ��ǥ
		{ 10600.f,(float)WINCY + 500.f },//32�� ������ ��ǥ,��� ������ǥ.
		 								 //3,4�������� ������ ���(upstair)
		//{ 6000.f,(float)WINCY - 750.f },//1�� ���.
		//{ 6100.f,(float)WINCY - 750.f },
		//{ 6100.f,(float)WINCY - 650.f },//2�� ���.
		//{ 6200.f,(float)WINCY - 650.f },
		//{ 6200.f,(float)WINCY - 550.f },//3�� ���.
		//{ 6300.f,(float)WINCY - 550.f },
		//{ 6300.f,(float)WINCY - 450.f },//4�� ���.
		//{ 6400.f,(float)WINCY - 450.f },
		//{ 6400.f,(float)WINCY - 350.f },//5�� ���.
		//{ 6500.f,(float)WINCY - 350.f },

	};

	for (int i = 0; i < 28; ++i)
	{
		m_LineList.push_back(new CLine(LLinePoint[i], LLinePoint[i + 1]));
	}
}
