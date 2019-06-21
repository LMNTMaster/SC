#include "Timer.h"

CTimer* CTimer::m_pInstance = NULL;

bool CTimer::Initialize()
{
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTime);

	m_fDeltaTime = 0.f;
	m_fTimeScale = 1.0f;

	return true;
}

void CTimer::Update()
{
	LARGE_INTEGER	tTime;
	QueryPerformanceCounter(&tTime);

	m_fDeltaTime = (tTime.QuadPart - m_tTime.QuadPart) / (float)m_tSecond.QuadPart;
	m_tTime = tTime;
}

CTimer::CTimer()
{
}


CTimer::~CTimer()
{
}
