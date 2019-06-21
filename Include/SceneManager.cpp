#include "SceneManager.h"
#include "Scene.h"
#include "Layer.h"
#include "Scenes\DefaultScene.h"
#include "Scenes\UnitEditScene.h"
#include "Scenes\SplashScene.h"
#include "Scenes\MainMenuScene.h"
#include "Scenes\MainGameScene.h"
#include "Timer.h"
#include "FogOfWarManager.h"
#include "Input.h"


CSceneManager* CSceneManager::m_pInstance = NULL;

CSceneManager::CSceneManager():
	m_pCurrentScene(NULL),
	m_pNextScene(NULL),
	m_bCurrentSceneInitialized(false),
	m_fUpdateCollisionTime(0.0f),
	m_iUpdateCollisionInSecond(60)
{
}


CSceneManager::~CSceneManager()
{
	if(m_pCurrentScene)
	delete m_pCurrentScene;

	if(m_pNextScene)
	delete m_pNextScene;
}

void CSceneManager::Initialize()
{	
	m_pCurrentScene = new CSplashScene;
}

void CSceneManager::PlayCurrentScene()
{
	if (!m_bCurrentSceneInitialized)
	{
		m_pCurrentScene->Initialize();
		m_bCurrentSceneInitialized = true;
	}	
		
	m_fUpdateCollisionTime += GET_SINGLE(CTimer)->GetDeltaTime();


	m_pCurrentScene->Start();
	if (m_fUpdateCollisionTime >= 1 / (float)m_iUpdateCollisionInSecond)
	{
		m_pCurrentScene->ClearContainUnitList();
		m_fUpdateCollisionTime -= 1 / (float)m_iUpdateCollisionInSecond;
		m_pCurrentScene->Collision();
	}
		
	m_pCurrentScene->Update();	
	m_pCurrentScene->Render();	
	m_pCurrentScene->LateUpdate();

	if(m_pCurrentScene->GetName().find("Game") != string::npos)
	GET_SINGLE(CFogOfWarManager)->CopyToPrev();

	GET_SINGLE(CFogOfWarManager)->ClearTileState();
	
	//m_pCurrentScene->Collision();

	if (m_pNextScene)
	{
		delete m_pCurrentScene;
		m_pCurrentScene = m_pNextScene;
		m_pNextScene = NULL;
	}
	
}

CScene * CSceneManager::CreateScene(const string & strSceneName, bool bSetCurrent)
{
	CScene* pScene = new CScene;

	if (bSetCurrent)
	{
		if(m_pCurrentScene)
		delete m_pCurrentScene;

		m_pCurrentScene = pScene;
	}
	
	return pScene;		
}

