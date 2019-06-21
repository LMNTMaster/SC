#pragma once
#include "../Component.h"
class CStructure :
	public CComponent
{
private:
	float m_fRequireMineral;
	float m_fRequireGas;

	float m_fSupply;
	float m_fBuildTime;
	float m_fBuildElipse;
	unsigned int m_iTextureTileWidth;
	unsigned int m_iTextureTileHeight;
	unsigned int m_iPositionX;
	unsigned int m_iPositionY;
	vector<CVector2> m_vecBuildableTile;
	//배치된 위치의 타일의 World상의 인덱스가 들어간다.
	vector<unsigned int> m_vecBuiltTileIndex;
	bool m_bVespeneGeyser;

public:
	void SetVespeneGeyser(bool bIsVespeneGeyser)
	{
		m_bVespeneGeyser = bIsVespeneGeyser;
	}
	bool GetVespeneGeyser() const
	{
		return m_bVespeneGeyser;
	}
	float GetRequireMineral() const
	{
		return m_fRequireMineral;
	}
	float GetRequireGas() const
	{
		return m_fRequireGas;
	}

	void SetRequireMineral(float fMineral)
	{
		m_fRequireMineral = fMineral;
	}
	void SetRequireGas(float fGas)
	{
		m_fRequireGas = fGas;
	}

	void SetSupply(float fSupply)
	{
		m_fSupply = fSupply;
	}
	float GetSupply() const
	{
		return m_fSupply;
	}
	void SetBuildTime(float fTime)
	{
		m_fBuildTime = fTime;
	}
	float GetBuildTime() const
	{
		return m_fBuildTime;
	}
	void SetBuildElipse(float fTime)
	{
		m_fBuildElipse = fTime;
	}
	float GetBuildElipse() const
	{
		return m_fBuildElipse;
	}

	void ClearBuildableTile()
	{
		m_vecBuildableTile.clear();
	}
	void AddBuiltTileIndex(unsigned int idx)
	{
		m_vecBuiltTileIndex.push_back(idx);
	}
	vector<unsigned int> GetBuiltTileIndex() const
	{
		return m_vecBuiltTileIndex;
	}
	void ClearBuiltTileIndex()
	{
		m_vecBuiltTileIndex.clear();
	}

	void AddBuildableTile(unsigned int iX, unsigned int iY)
	{
		m_vecBuildableTile.push_back(CVector2(iX, iY));
	}
	vector<CVector2> GetBuildableTile() const
	{
		return m_vecBuildableTile;
	}
	void SetPosition(unsigned int iX, unsigned int iY);
	
	void SetPosition(CVector2 pos)
	{
		m_iPositionX = pos.x;
		m_iPositionX = pos.y;
	}

	void SetSize(CVector2 size)
	{
		m_iTextureTileWidth = size.x;
		m_iTextureTileHeight = size.y;
	}
	void SetSize(unsigned int iWidth, unsigned int iHeight)
	{
		m_iTextureTileWidth = iWidth;
		m_iTextureTileHeight = iHeight;
	}

	CVector2 GetPosition() const
	{
		return CVector2(m_iPositionX, m_iPositionY);
	}
	CVector2 GetSize() const
	{
		return CVector2(m_iTextureTileWidth, m_iTextureTileHeight);
	}
public:
	void Start() override;
	void Update() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;
public:
	CStructure(const CStructure& component);
	CStructure();
	~CStructure();
};

