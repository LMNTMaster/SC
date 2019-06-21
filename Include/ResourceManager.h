#pragma once
#include "Game.h"

class CResourceManager
{
private:
	static CResourceManager* m_pInstance;
public :
	static CResourceManager* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CResourceManager;
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
	CResourceManager();
	~CResourceManager();

	
private:
	unordered_map<string, wstring> m_mapPath;
	unordered_map<string, class CTexture*> m_mapTexture;
	unordered_map<string, class CSprite*> m_mapSprite;
	unordered_map<string, class CGameObject*> m_mapUnit;
	unordered_map<int, vector<class CTile*>> m_mapTileSet;
	unordered_map<int, class CTile*> m_mapTile;	
	unordered_map<string, PSOUNDINFO>	m_mapSound;

	System*		m_pSoundSystem;
	Channel*	m_pSoundChannel[ST_END];

	class CTexture*	m_pBackBuffer;
	HWND m_hWnd;
	HINSTANCE m_hInst;
	HDC		m_hDC;
	bool		m_bInitialized;

public:

	HDC GetMemberDC() const
	{
		return m_hDC;
	}
	void AddTile(int iKey, class CTile* pTile);
	void AddTileSet(int iKey, vector<class CTile*> tileSet);
	const unordered_map<int, vector<class CTile*>>& GetTileSetMap() const;
	const vector<class CTile*>& GetTileSet(int iKey) const;
	class CTile* GetTile(int iKey);
	class CTile* GetRandomTileFromTileSet(int iKey);
	class CTile* GetRandomTileFromTileSet(int iKey, int iKey2);
	class CGameObject* FindUnit(const string& strKey);
	class CTexture* GetBackBuffer() const
	{
		return m_pBackBuffer;
	}
	bool Initialize();
	void AddTextureToMap(const string& strKey, class CTexture* pTexture);
	class CTexture * FindTexture(const string & strKey);
	class CSprite* FindSprite(const string& strKey);
	class CTexture * LoadTexture(const string & strKey, const wchar_t * pFileName, const string & strPathKey);
	class CSprite* LoadSprite(const string& strKey, const wchar_t* pFileName, const string& strPathKey);
	bool LoadSound(const string & strKey, bool bLoop, const char * pFileName, const string & strPathKey);

	PSOUNDINFO FindSound(const string& strKey);

	bool PlaySFX(const string& strKey);
	void StopSFX(SOUND_TYPE eType);
	void SetVolume(SOUND_TYPE eType, float fVolume);

	void AddUnit(const string& strKey, class CGameObject* pUnit);
	void AddSprite(const string& strKey, class CSprite* pSprite);
	bool CreatePath(const string & strKey, const wchar_t * pPath, const string & strBaseKey = ROOT_PATH);
	const wchar_t* FindPath(const string& strKey);
	const char * CResourceManager::FindPathMultiByte(const string & strKey);

};

