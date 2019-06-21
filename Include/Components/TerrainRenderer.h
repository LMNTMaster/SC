#pragma once
#include "../Game.h"
#include "../Renderer.h"
class CTerrainRenderer :
	public CRenderer
{
private:
	vector<class CTile*> m_vecTile;

public:
	class CTile* GetTile(unsigned int idx) const
	{
		return m_vecTile[idx];
	}
	void AddTile(class CTile* pTile);
	void ChangeTile(unsigned int index , class CTile* pTile);
	void ChangeTile(unsigned int index, int iTileKey);
	void ChangeRandomTileFromTileSet(unsigned int index, int iTileSetKey);
	void ChangeRandomTileFromTileSet(unsigned int index, int iTileSetKey, int iTileSetKey2);
	void LoadMap();
	void Render() override;
	

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;


public:
	CTerrainRenderer(const CTerrainRenderer& component);
	CTerrainRenderer();
	~CTerrainRenderer();
};

