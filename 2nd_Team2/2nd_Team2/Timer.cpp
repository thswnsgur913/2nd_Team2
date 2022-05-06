#include "stdafx.h"
#include "Timer.h"

CTimer::CTimer():
	m_iCurrentTime(0),
	m_iRepeatRate(0),
	m_iCurrentCount(0),
	m_bRunTimer(false) {

}

CTimer::~CTimer() {

}

void CTimer::StartTimer(const float _repeatRateSecond, std::function<void()> _pCallBack) {
  	m_iRepeatRate = _repeatRateSecond;
	pExcuteCallBack = _pCallBack;

	m_iCurrentTime = static_cast<int>(GetTickCount64());
	m_iCurrentCount = TIMESCALE;
	m_bRunTimer = true;
}

void CTimer::Update() {
	if (!pExcuteCallBack || !m_bRunTimer)
		return;

	DWORD currentTime = static_cast<DWORD>(GetTickCount64());

	if (TICKSCALE <= currentTime - m_iCurrentTime) {
		m_iCurrentCount += TIMESCALE;

		if (m_iCurrentCount >= m_iRepeatRate) {
			m_iCurrentCount = 0;
			
			pExcuteCallBack();
		}
	}

	// Á¤¹Ðµµ°¡ ¹º°¡ ¶³¾îÁü...
	// 3f·Î ¼³Á¤ÇÏ¸é 6ÃÊÈÄ ½ÇÇàµÊ..

	m_iCurrentTime = currentTime;
}