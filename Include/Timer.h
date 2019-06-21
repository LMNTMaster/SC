#pragma once
#include "Game.h"

class CTimer
{

private:
	CTimer();
	~CTimer();
private:
	static CTimer* m_pInstance;
public:
	static CTimer* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CTimer;
		}
		return m_pInstance;
	}
	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

private:
	LARGE_INTEGER	m_tSecond;
	LARGE_INTEGER	m_tTime;
	float		m_fDeltaTime;
	float		m_fTimeScale;

public:
	float GetDeltaTime() const
	{
		return m_fDeltaTime * m_fTimeScale;
	}
	float GetTimeScale()const
	{
		return m_fTimeScale ;
	}
	float GetUnscaledDeltaTime()const
	{
		return m_fDeltaTime;
	}
	void SetTimeScale(float tTimeScale)
	{
		m_fTimeScale = tTimeScale;
	}


public:
	bool Initialize();
	void Update();


};
