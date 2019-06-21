#pragma once
#include "../Component.h"
class CPlayer :
	public CComponent
{
private:
	string m_strName;
	TEAM_COLOR m_eTeamColor;
	RACE_TYPE m_eRaceType;
	unsigned int m_iMineral;
	unsigned int m_iVespeneGas;
	unsigned int m_iMaxPopulation;
	unsigned int m_iCurrentPopulation;
	unsigned int m_pUpgradeState[UT_END];

	class CGameObject* m_pMineralText;
	class CGameObject* m_pGasText;
	class CGameObject* m_pSupplyText;

public:
	bool FindOwnedStructure(const string& strStructureName);
	
	void SetTextObject(class CGameObject* pMineral, class CGameObject* pGas, class CGameObject* pSupply)
	{
		m_pMineralText = pMineral;
		m_pGasText = pGas;
		m_pSupplyText = pSupply;
	}
	void SetMineralTextObject(class CGameObject* pMineral)
	{
		m_pMineralText = pMineral;
	}
	void SetGasTextObject(class CGameObject* pGas)
	{
		m_pGasText = pGas;
	}
	void SetSupplyTextObject(class CGameObject* pSupply)
	{
		m_pSupplyText = pSupply;
	}

	unsigned int GetUpgrade(UPGRADE_TYPE type);
	void SetUpgrade(UPGRADE_TYPE type, unsigned int iValue);

	void SetTeamColor(TEAM_COLOR eTeamColor)
	{
		m_eTeamColor = eTeamColor;
	}
	void SetPlayerName(const string& strName)
	{
		m_strName = strName;
	}
	void SetRaceType(RACE_TYPE eRaceType)
	{
		m_eRaceType = eRaceType;
	}

	void AddMineral(unsigned int iMineral)
	{
		m_iMineral += iMineral;
	}
	void SetMineral(unsigned int iMineral)
	{
		m_iMineral = iMineral;
	}
	void AddVespeneGas(unsigned int iGas)
	{
		m_iVespeneGas += iGas;
	}
	void SetVespeneGas(unsigned int iGas)
	{
		m_iVespeneGas = iGas;
	}
	void SetMaxPopulation(unsigned int iPopulation)
	{
		m_iMaxPopulation = iPopulation;
	}
	void AddMaxPopulation(unsigned int iPopulation)
	{
		m_iMaxPopulation += iPopulation;
	}

	void SetCurrentPopulation(unsigned int iPopulation)
	{
		m_iCurrentPopulation = iPopulation;
	}

	void AddCurrentPopulation(unsigned int iPopulation)
	{
		m_iCurrentPopulation += iPopulation;
	}


	TEAM_COLOR GetTeamColor() const
	{
		return m_eTeamColor;
	}
	string GetPlayerName() const
	{
		return m_strName;
	}
	RACE_TYPE GetRaceType() const
	{
		return m_eRaceType;
	}
	unsigned int GetMineral() const
	{
		return m_iMineral;
	}
	unsigned int GetVespeneGas() const
	{
		return m_iVespeneGas;
	}
	unsigned int GetMaxPopulation() const
	{
		return m_iMaxPopulation;
	}
	unsigned int GetCurrentPopulation() const
	{
		return m_iCurrentPopulation;
	}
	

public:
	void Update() override;

public:
	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile) override;
	CComponent* clone() override;


public:
	CPlayer(const CPlayer& component);
	CPlayer();
	~CPlayer();
};

