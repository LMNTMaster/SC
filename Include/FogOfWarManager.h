#pragma once
#include "Game.h"

class CFogOfWarManager
{
private:
	static CFogOfWarManager* m_pInstance;

public:
	static CFogOfWarManager* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CFogOfWarManager;
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
	vector<FOW> m_vecTile;
	vector<FOW> m_vecPrevTile;

public:
	void SetTileSize(int iWidth, int iHeight);
	void SetTileState(int index, FOW_STATE eState, bool bVisit);
	FOW GetTileState(int index)
	{
		if(m_vecTile.size() > 0)
			return m_vecTile[index];
	}
	int GetTileCount() const
	{
		return m_vecTile.size();
	}
	void SetPrevTileState(int index, FOW_STATE eState, bool bVisit);
	void SetPrevTileState(int index, FOW tFOW);
	FOW GetPrevTileState(int index)
	{
		return m_vecPrevTile[index];
	}

	void CopyToPrev();
	void ClearTileState();


public:
	void Initialize();


public:
	CFogOfWarManager();
	~CFogOfWarManager();
};

