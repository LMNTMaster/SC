#pragma once
#include "Game.h"

class CCore
{
private:
	CCore();
	~CCore();

private:
	static CCore* m_pInstance;

public :
	static CCore* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCore;
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
	static bool		m_bLoop;

private:
	HINSTANCE		m_hInst;
	HWND				m_hWnd;
	HDC				m_hDC;
	HDC				m_hBackDC;
	CVector2		m_ScreenSize;

	thread* m_pLoadingThread;

	unsigned int m_iProgress;
	unsigned int m_iMaxProgress;

public :

	thread* GetLoadingThread() const
	{
		return m_pLoadingThread;
	}

	static void Loading();
	

	float GetLoadingProgress() const
	{
		return (float)m_iProgress / (float)m_iMaxProgress;
	}

	HWND GetWindowHandle() const
	{
		return m_hWnd;
	}
	HINSTANCE GetInstanceHandle() const
	{
		return m_hInst;
	}
	HDC GetCurrentDC() const
	{
		return m_hDC;
	}
	HDC GetBackDC() const
	{
		//return m_hDC;
		return m_hBackDC;
	}
	CVector2 GetScreenSize() const
	{
		return m_ScreenSize;
	}

	void ExitGame() 
	{
		DestroyWindow(m_hWnd);
	}

private:
	ATOM MyRegisterClass();
	BOOL Create();
	void Logic();

public:
	
	bool	Init(HINSTANCE hInst);
	int		Run();
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


};

