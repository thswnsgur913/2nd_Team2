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

	m_iCurrentTime = GetTickCount64();
	m_iCurrentCount = TIMESCALE;
	m_bRunTimer = true;
}

void CTimer::Update() {
	if (!pExcuteCallBack || !m_bRunTimer)
		return;

	DWORD currentTime = GetTickCount64();

	if (TICKSCALE <= currentTime - m_iCurrentTime) {
		m_iCurrentCount += TIMESCALE;

		if (m_iCurrentCount >= m_iRepeatRate) {
			m_iCurrentCount = 0;
			
			pExcuteCallBack();
		}
	}

	// 정밀도가 뭔가 떨어짐...
	// 3f로 설정하면 6초후 실행됨..

	m_iCurrentTime = currentTime;
}