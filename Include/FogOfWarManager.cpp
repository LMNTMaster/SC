#include "FogOfWarManager.h"

CFogOfWarManager* CFogOfWarManager::m_pInstance = NULL;

void CFogOfWarManager::SetTileSize(int iWidth, int iHeight)
{
	m_vecTile.resize(iWidth * iHeight);
	memset(&m_vecTile[0], 0, sizeof(FOW) * iWidth * iHeight);
	m_vecPrevTile.resize(iWidth * iHeight);
	memset(&m_vecPrevTile[0], 0, sizeof(FOW) * iWidth * iHeight);
}

void CFogOfWarManager::SetTileState(int index, FOW_STATE eState, bool bVisit)
{
	m_vecTile[index].m_eState = eState;
	m_vecTile[index].m_bVisit = bVisit;
}

void CFogOfWarManager::SetPrevTileState(int index, FOW_STATE eState, bool bVisit)
{
	m_vecPrevTile[index].m_eState = eState;
	m_vecPrevTile[index].m_bVisit = bVisit;
}

void CFogOfWarManager::SetPrevTileState(int index, FOW tFOW)
{
	m_vecPrevTile[index] = tFOW;
}

void CFogOfWarManager::CopyToPrev()
{
	memcpy(&m_vecPrevTile[0], &m_vecTile[0], sizeof(FOW) * m_vecTile.size());
}

void CFogOfWarManager::ClearTileState()
{
	int iSize = m_vecTile.size();
	for (int i = 0; i < iSize; ++i)
	{
		m_vecTile[i].m_eState = FS_INVISIBLE;
	}
}

void CFogOfWarManager::Initialize()
{
}

CFogOfWarManager::CFogOfWarManager()
{
}


CFogOfWarManager::~CFogOfWarManager()
{
}
