#include "ResourceManager.h"
#include "Texture.h"
#include "Core.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Tile.h"

CResourceManager* CResourceManager::m_pInstance = NULL;

void CResourceManager::AddTile(int iKey, CTile * pTile)
{
	m_mapTile.insert(make_pair(iKey, pTile));
}

void CResourceManager::AddTileSet(int iKey, vector<class CTile*> tileSet)
{
	m_mapTileSet.insert(make_pair(iKey, tileSet));
}

const unordered_map<int, vector<class CTile*>>& CResourceManager::GetTileSetMap() const
{
	return m_mapTileSet;
}

const vector<class CTile*>& CResourceManager::GetTileSet(int iKey) const
{
	unordered_map<int, vector<CTile*>>::const_iterator iter = m_mapTileSet.find(iKey);

	if (iter == m_mapTileSet.end())
	{
		vector<CTile*> tempEmpty;
		return tempEmpty;
	}

	return iter->second;
}

CTile * CResourceManager::GetTile(int iKey)
{
	unordered_map<int, CTile*>::iterator iter = m_mapTile.find(iKey);
	if (iter == m_mapTile.end())
		return NULL;

	return iter->second;
}

CTile * CResourceManager::GetRandomTileFromTileSet(int iKey)
{
	unordered_map<int, vector<CTile*>>::iterator iter = m_mapTileSet.find(iKey);

	if (iter == m_mapTileSet.end())
		return NULL;

	int idx = rand() % iter->second.size();
	return iter->second[idx];
}

CTile * CResourceManager::GetRandomTileFromTileSet(int iKey, int iKey2)
{
	vector<CTile*> temp;
	unordered_map<int, vector<CTile*>>::iterator iter = m_mapTileSet.find(iKey);
	unordered_map<int, vector<CTile*>>::iterator iter2 = m_mapTileSet.find(iKey2);

	if (iter == m_mapTileSet.end() || iter2 == m_mapTileSet.end())
		return NULL;

	temp.insert(temp.begin(), iter->second.begin(), iter->second.end());
	temp.insert(temp.begin(), iter2->second.begin(), iter2->second.end());

	int idx = rand() % temp.size();
	return temp[idx];
}

CGameObject * CResourceManager::FindUnit(const string & strKey)
{
	unordered_map<string, CGameObject*>::iterator iter = m_mapUnit.find(strKey);

	if (iter == m_mapUnit.end())
		return NULL;

	return iter->second;
}

bool CResourceManager::Initialize()
{
	m_hInst = GET_SINGLE(CCore)->GetInstanceHandle();
	m_hWnd = GET_SINGLE(CCore)->GetWindowHandle();
	m_hDC = GET_SINGLE(CCore)->GetCurrentDC();
	wchar_t	strPath[LONG_MAX_PATH] = {};

	GetModuleFileName(NULL, strPath, LONG_MAX_PATH);

	for (int i = lstrlen(strPath) - 1; i >= 0; --i)
	{
		if (strPath[i] == '/' || strPath[i] == '\\')
		{
			memset(strPath + (i + 1), 0, sizeof(wchar_t) *
				(LONG_MAX_PATH - (i + 1)));
			break;
		}
	}

	m_mapPath.insert(make_pair(ROOT_PATH, strPath));

	// Texture 경로 설정
	if (!CreatePath(TEXTURE_PATH, L"Texture\\"))
		return false;
	if (!CreatePath(UI_TEXTURE_PATH, L"Texture\\UI\\"))
		return false;
	if (!CreatePath(UNIT_TEXTURE_PATH, L"Texture\\Unit\\"))
		return false;
	if (!CreatePath(BUILDING_TEXTURE_PATH, L"Texture\\Building\\"))
		return false;
	if (!CreatePath(TILESET_TEXTURE_PATH, L"Texture\\Tileset\\"))
		return false;
	if (!CreatePath(VFX_PATH, L"Texture\\VFX\\"))
		return false;
	if (!CreatePath(SFX_PATH, L"Sound\\SFX\\"))
		return false;
	if (!CreatePath(BGM_PATH, L"Sound\\BGM\\"))
		return false;
	if (!CreatePath(VOICE_PATH, L"Sound\\Voice\\"))
		return false;
	if (!CreatePath(UNIT_PATH, L"Units\\"))
		return false;
	if (!CreatePath(CACHE_PATH, L"Cache\\"))
		return false;
	if (!CreatePath(ANIMATION_CLIP_PATH, L"AnimationClip\\"))
		return false;
	if (!CreatePath(MAP_PATH, L"Maps\\"))
		return false;

	//게임 로드하면서 여기서 리소스 로드 처리할 것
	//로드 위치는 윈도우 생성 이후, Splash Scene 중임
	m_pBackBuffer = LoadTexture("BackBuffer", L"BackBuffer.bmp", UI_TEXTURE_PATH);

	m_bInitialized = true;


	System_Create(&m_pSoundSystem);
	m_pSoundSystem->init(10, FMOD_INIT_NORMAL, NULL);

	return true;
}

void CResourceManager::AddTextureToMap(const string & strKey, CTexture * pTexture)
{
	m_mapTexture.insert(make_pair(strKey, pTexture));
}

bool CResourceManager::CreatePath(const string & strKey, const wchar_t * pPath, const string & strBaseKey)
{
	const wchar_t* pBasePath = FindPath(strBaseKey);

	wstring	strPath;

	if (pBasePath)
		strPath = pBasePath;

	strPath += pPath;

	m_mapPath.insert(make_pair(strKey, strPath));

	return true;
}

const wchar_t * CResourceManager::FindPath(const string & strKey)
{
	unordered_map<string, wstring>::iterator	iter = m_mapPath.find(strKey);

	if (iter == m_mapPath.end())
		return NULL;

	return iter->second.c_str();
}

const char * CResourceManager::FindPathMultiByte(const string & strKey)
{
	const wchar_t*	pPath = FindPath(strKey);

	if (!pPath)
		return NULL;
	
	char tempPath[LONG_MAX_PATH];

	memset(tempPath, 0, sizeof(char) * LONG_MAX_PATH);

	WideCharToMultiByte(CP_ACP, 0, pPath, -1, tempPath,	lstrlen(pPath), 0, 0);

	return tempPath;
}


CTexture * CResourceManager::LoadTexture(const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	CTexture*	pTexture = FindTexture(strKey);

	if (pTexture)
		return pTexture;

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(m_hInst, m_hDC, strKey, pFileName,	strPathKey))
	{
		delete pTexture;
		return NULL;
	}

	pTexture->SetTextureKey(strKey);
	m_mapTexture.insert(make_pair(strKey, pTexture));

	return pTexture;
}

CSprite * CResourceManager::LoadSprite(const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	CSprite*	pSprite = FindSprite(strKey);

	if (pSprite)
		return pSprite;

	pSprite = new CSprite;

	if (!pSprite->LoadSprite(strKey, pFileName, strPathKey))
	{
		delete pSprite;
		return NULL;
	}

	pSprite->SetSpriteKey(strKey);
	m_mapSprite.insert(make_pair(strKey, pSprite));

	return pSprite;
}

bool CResourceManager::LoadSound(const string & strKey, bool bLoop, const char * pFileName, const string & strPathKey)
{
		if (FindSound(strKey))
			return true;

		char	pPath[LONG_MAX_PATH] = {};		
		const char* tempPath = GET_SINGLE(CResourceManager)->FindPathMultiByte(strPathKey);

		strcpy(pPath, tempPath);
		string	strFullPath;

		if (pPath)
		{
			strFullPath = string(pPath);
		}

		strFullPath += string(pFileName);

		FMOD_MODE	eMode = FMOD_LOOP_NORMAL;

		if (!bLoop)
			eMode = FMOD_DEFAULT;

		PSOUNDINFO	pSoundInfo = new SOUNDINFO;

		pSoundInfo->bLoop = bLoop;
		m_pSoundSystem->createSound(strFullPath.c_str(), eMode, NULL, &pSoundInfo->pSound);

		m_mapSound.insert(make_pair(strKey, pSoundInfo));
			
		return true;
}

PSOUNDINFO CResourceManager::FindSound(const string & strKey)
{
	unordered_map<string, PSOUNDINFO>::iterator	iter = m_mapSound.find(strKey);

	if (iter == m_mapSound.end())
		return NULL;

	return iter->second;	
}

bool CResourceManager::PlaySFX(const string & strKey)
{
	PSOUNDINFO	pSound = FindSound(strKey);

	if (!pSound)
		return false;

	m_pSoundSystem->update();

	SOUND_TYPE	eType = ST_BGM;

	if (!pSound->bLoop)
		eType = ST_SFX;

	m_pSoundSystem->playSound(pSound->pSound, NULL, false, &m_pSoundChannel[eType]);

	return true;
}

void CResourceManager::StopSFX(SOUND_TYPE eType)
{
	m_pSoundChannel[eType]->stop();
}

void CResourceManager::SetVolume(SOUND_TYPE eType, float fVolume)
{
	m_pSoundChannel[eType]->setVolume(fVolume);
}


void CResourceManager::AddUnit(const string & strKey, CGameObject * pUnit)
{
	if (!FindUnit(strKey))
	{
		m_mapUnit.insert(make_pair(strKey, pUnit));
	}

}

void CResourceManager::AddSprite(const string & strKey, CSprite* pSprite)
{
	if (!FindSprite(strKey))
	{
		m_mapSprite.insert(make_pair(strKey, pSprite));
	}
}


CTexture * CResourceManager::FindTexture(const string & strKey)
{
	unordered_map<string, class CTexture*>::iterator	iter = m_mapTexture.find(strKey);

	if (iter == m_mapTexture.end())
		return NULL;

	return iter->second;
}

CSprite * CResourceManager::FindSprite(const string & strKey)
{
	unordered_map<string, CSprite*>::iterator iter = m_mapSprite.find(strKey);
	if (iter == m_mapSprite.end())
		return NULL;

	return iter->second;
}


CResourceManager::CResourceManager():
	m_bInitialized(false),
	m_pSoundSystem(NULL),
	m_hDC(NULL)
{
}


CResourceManager::~CResourceManager()
{
	if (m_pBackBuffer)
	{
		unordered_map<string, CTexture*>::iterator iter = m_mapTexture.find("BackBuffer");
		delete m_pBackBuffer;
		m_mapTexture.erase(iter);
	}

	{
		unordered_map<string, CTexture*>::iterator	iter;
		unordered_map<string, CTexture*>::iterator iterEnd = m_mapTexture.end();

		for (iter = m_mapTexture.begin(); iter != iterEnd; ++iter)
		{
			if (iter->second)
				delete iter->second;
		}
		m_mapTexture.clear();
	}


	{
		unordered_map<string, CSprite*>::iterator	iter;
		unordered_map<string, CSprite*>::iterator iterEnd = m_mapSprite.end();

		for (iter = m_mapSprite.begin(); iter != iterEnd; ++iter)
		{
			if (iter->second)
				delete iter->second;
		}
		m_mapSprite.clear();
	}


	{
		unordered_map<string, CGameObject*>::iterator iter;
		unordered_map<string, CGameObject*>::iterator iterEnd = m_mapUnit.end();

		for (iter = m_mapUnit.begin(); iter != iterEnd; ++iter)
		{
			if (iter->second)
				delete iter->second;
		}
		m_mapUnit.clear();
	}


	{
		m_mapTileSet.clear();
		// 타일이 타일셋 안에 종속되어져 있으므로, 메모리 해제는 타일에서만 하도록 한다.

		unordered_map<int, CTile*>::iterator iter;
		unordered_map<int, CTile*>::iterator iterEnd = m_mapTile.end();
		for (iter = m_mapTile.begin(); iter != iterEnd; ++iter)
		{
			if (iter->second)
				delete iter->second;
		}
		m_mapTile.clear();
	}

	{
		unordered_map<string, PSOUNDINFO>::iterator	iter;
		for (iter = m_mapSound.begin(); iter != m_mapSound.end(); ++iter)
		{
			iter->second->pSound->release();
			if (iter->second)
				delete iter->second;
		}
		m_mapSound.clear();

		m_pSoundSystem->close();
		m_pSoundSystem->release();
	}
}
