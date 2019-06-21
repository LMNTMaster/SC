#pragma once
#include "Game.h"
class CMinimapManager
{
private:
	static CMinimapManager* m_pInstance;

public:
	static CMinimapManager* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CMinimapManager;

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
	vector<COLORREF> m_vecTerrainPixel;

public:
	const vector<COLORREF>& GetTerrainPixel() const
	{
		return m_vecTerrainPixel;
	}
	void CreateTerrainImage(class CScene* pScene, class CTerrainRenderer* pTerrainRenderer);
	CVector2 GetRelativeCameraPosition();
	CVector2 GetRelaticeCameraSize();

	void Initialize();




private:
	CMinimapManager();
	~CMinimapManager();
};

