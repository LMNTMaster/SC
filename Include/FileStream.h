#pragma once
#include "Game.h"

class CFileStream
{
private:
	static CFileStream* m_pInstance;

public:
	static CFileStream* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CFileStream;
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
	CFileStream();
	~CFileStream();

private:
	unordered_map<string, class CSprite*> m_mapAnimationClip;
	Color m_pPaletteColor[8];

public :
	void Initialize();

public:
	void LoadMap(class CScene* pScene, class CLayer* pTerrainLayer, class CTerrainRenderer* pTerrainRenderer, const string& strFileName);
	vector<PIXEL>*  LoadBMP(class CTexture* pTexture);
	void SaveBMP(const class CTexture* pTexture);
	void SaveBMP(const char* fileName, BITMAPFILEHEADER fh, BITMAPINFOHEADER ih, vector<PIXEL>* pPixels);
	class CTexture* SetTeamColor(size_t iPlayerIndex, const string& strColor ,const wstring& strCacheBaseDirectory, CTexture * pTexture);
	class CSprite* LoadAnimationClip(const string& strKey, const wchar_t* pFileName, const string& strPath);
	void SaveAnimationClip(const class CSprite* pSprite);
	class CTexture* MergeTexture(const class CTexture* pBase, const class CTexture* pAlpha, const class CTexture* pCover);
	class CTexture* SaveTexture(const class CTexture* pTexture);
	class CTexture* LoadPalette(const char* fileName);

	void SaveUnit(class CGameObject* pGameObject , const string& strFileName);
	void LoadUnit(const string& key , const string& strFileName);
}
;
