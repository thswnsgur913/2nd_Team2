#pragma once
class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	const float& Get_ScrollX(void) { return m_ScrollX; }
	void Set_ScrollX(float fXX) { m_ScrollX += fXX; }
	const float& Get_ScrollY(void) { return m_ScrollY; }
	void Set_ScrollY(float fYY) { m_ScrollY += fYY; }

public:
	static CScrollMgr* Get_Scroll(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScrollMgr;
		}
		return m_pInstance;
	}

	static void Destroy_Scroll(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr* m_pInstance;
	float m_ScrollX = 0.f;
	float m_ScrollY = 0.f;
};

