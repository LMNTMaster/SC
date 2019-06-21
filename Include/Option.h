#pragma once
#include "Game.h"

//후에 파일로 읽어서 설정 하도록 함.
class COption
{
private:
	static COption* m_pInstance;

public:
	static COption* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new COption;
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

public :
	void Initialize();

private:
	float m_fCameraMoveSpeed;
	bool m_bCursorClipped;

public :
	bool GetCursorClipped() const
	{
		return m_bCursorClipped;
	}
	float GetCameraSpeed() const
	{
		return m_fCameraMoveSpeed;
	}
	void SetCameraSpeed(float fSpeed)
	{
		m_fCameraMoveSpeed = fSpeed;
	}
	void SetCursorClipped(bool bClipped)
	{
		m_bCursorClipped = bClipped;
	}




private:
	COption();
	~COption();
};

