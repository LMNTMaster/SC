#pragma once
#include "Component.h"

//Require to Render Setting : WorldPosition, Camera , BaseTexture, Size, IndexPos
class CTile
{

private:
	int m_iTileSetID;
	int m_iTileID;
	unsigned int m_iTileIndex;
	class CTexture* m_pBaseTexture;
	class CTexture* m_pGreyScaleTexture;
	class CTexture* m_pCreepTexture;
	CVector2 m_WorldPosition;
	unsigned int m_iWidth;
	unsigned int m_iHeight;
	unsigned int m_iX;
	unsigned int m_iY;
	class CCamera* m_pCamera;
	unsigned int m_iTerrainHeight;
	bool m_bMovable;
	bool m_bCreep;
	bool m_bBuildable;
	RESOURCE_TYPE m_eResourceType;
	list<class CGameObject*> m_ContainUnitList;

public:
	void SetResourceType(RESOURCE_TYPE eType)
	{
		m_eResourceType = eType;
	}
	RESOURCE_TYPE GetResourceType() const
	{
		return m_eResourceType;
	}
	const list<class CGameObject*>& GetContainUnitList() const
	{
		return m_ContainUnitList;
	}

	void AddUnit(class CGameObject* pGameObject)
	{
		m_ContainUnitList.push_back(pGameObject);
	}

	void ClearList()
	{
		m_ContainUnitList.clear();
	}

	class CTexture* GetGreyScaleTexture() const
	{
		return m_pGreyScaleTexture;
	}

	void SetGreyScaleTexture(class CTexture* pTexture)
	{
		m_pGreyScaleTexture = pTexture;
	}
	
	class CTexture* GetCreepTexture() const
	{
		return m_pCreepTexture;
	}


	unsigned int GetTileIndex() const
	{
		return m_iTileIndex;
	}
	void SetTileIndex(unsigned int idx)
	{
		m_iTileIndex = idx;
	}
	class CTexture* GetBaseTexture() const
	{
		return m_pBaseTexture;
	}

	void SetCreepTexture(class CTexture* pTexture)
	{
		m_pCreepTexture = pTexture;
	}

	void SetBaseTexture(class CTexture* pTexture)
	{
		m_pBaseTexture = pTexture;
	}

	void SetTileSetID(int id)
	{
		m_iTileSetID = id;
	}
	void SetTileID(int id)
	{
		m_iTileID = id;
	}

	void SetTerrainHeight(unsigned int iHeight)
	{
		m_iTerrainHeight = iHeight;
	}
	void SetMovable(bool bMovable)
	{
		m_bMovable = bMovable;
	}
	void SetCreep(bool bCreep)
	{
		m_bCreep = bCreep;
	}
	void SetBuildable(bool bBuildable)
	{
		m_bBuildable = bBuildable;
	}

	int GetTileSetID() const
	{
		return m_iTileSetID;
	}
	int GetTileID() const
	{
		return m_iTileID;
	}

	unsigned int GetTerrainHeight() const
	{
		return m_iTerrainHeight;
	}
	bool GetMovable() const
	{
		return m_bMovable;
	}
	bool GetCreep() const
	{
		return m_bCreep;
	}
	bool GetBuildable() const
	{
		return m_bBuildable;
	}

	void SetCamera(class CCamera* pCamera)
	{
		m_pCamera = pCamera;
	}
	class CCamera* GetCamera() const
	{
		return m_pCamera;
	}

	void SetWorldPosition(CVector2 pos)
	{
		m_WorldPosition = pos;
	}
	CVector2 GetWorldPosition	() const
	{
		return m_WorldPosition;
	}

	void SetOffset(unsigned int x, unsigned int y)
	{
		m_iX = x;
		m_iY = y;
	}
	CVector2 GetOffset() const
	{
		return CVector2(m_iX, m_iY);
	}


	void RenderTileTexture();
	void RenderTileTexture(FOW tState);
	
public:
	CTile* clone();

public:
	CTile(const CTile&);
	CTile();
	~CTile();
};

