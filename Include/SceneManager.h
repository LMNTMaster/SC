#pragma once
#include "Game.h"


class CSceneManager
{
private:
	static CSceneManager* m_pInstance;
private:
	CSceneManager();
	~CSceneManager();
public :
	static CSceneManager* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneManager;
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
	bool					m_bCurrentSceneInitialized;
	class CScene* m_pCurrentScene;
	class CScene* m_pNextScene;
	float				m_fUpdateCollisionTime;
	int					m_iUpdateCollisionInSecond;
	
public :
	void Initialize();

public :
	void PlayCurrentScene();

public:
	class CScene* CreateScene(const string& strSceneName, bool bSetCurrent);;
	void SetCurrentScene(class CScene* pScene)
	{
		if (m_pCurrentScene)
		{
			delete m_pCurrentScene;
		}
		m_pCurrentScene = pScene;
		m_bCurrentSceneInitialized = false;
	}
	class CScene* GetCurrentScene() const
	{
		return m_pCurrentScene;
	}
	void SetNextScene(class CScene* pScene)
	{
		m_pNextScene = pScene;
	}
	class CScene* GetNextScene() const
	{
		return m_pNextScene;
	}


};

