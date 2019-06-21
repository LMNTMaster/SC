#include "Player.h"
#include "TextRenderer.h"
#include "../GameObject.h"
#include "../Layer.h"
#include "../Scene.h"
#include "../Input.h"

bool CPlayer::FindOwnedStructure(const string & strStructureName)
{	

	list<CGameObject*> pGroundTargetList = m_pGameObject->GetScene()->FindLayer("GroundUnit")->FindGameObjects(strStructureName);
	list<CGameObject*> pAirTargetList = m_pGameObject->GetScene()->FindLayer("AirUnit")->FindGameObjects(strStructureName);

	pGroundTargetList.insert(pGroundTargetList.begin(), pAirTargetList.begin(), pAirTargetList.end());

	list<CGameObject*>::iterator iter;
	list<CGameObject*>::iterator iterEnd = pGroundTargetList.end();

	for (iter = pGroundTargetList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetPilot() == this)
		{
			return true;
		}
	}

	return false;
}

//해당 타입을 찾지 못하면 -1 리턴
unsigned int CPlayer::GetUpgrade(UPGRADE_TYPE type)
{
	return m_pUpgradeState[(int)type] ;
}

void CPlayer::SetUpgrade(UPGRADE_TYPE type, unsigned int iValue)
{
	m_pUpgradeState[(int)type] = iValue;
}

void CPlayer::Update()
{
	if (m_pGameObject->GetScene()->GetName().find("Game") != string::npos)
	{
		char strMineral[32] = {};
		char strGas[32] = {};
		char strMaxSupply[32] = {};
		char strCurrSupply[32] = {};

		itoa(m_iMineral, strMineral, 10);
		itoa(m_iVespeneGas, strGas, 10);
		itoa(m_iMaxPopulation, strMaxSupply, 10);
		itoa(m_iCurrentPopulation, strCurrSupply, 10);

		string tempMineral(strMineral);
		string tempGas(strGas);
		string tempSupply(strCurrSupply + string("/") + strMaxSupply);

		if (this->GetPlayerName() == "Eunsoo")
		{		
			m_pMineralText->GetComponent<CTextRenderer>()->SetText(wstring(tempMineral.begin(), tempMineral.end()));
			m_pGasText->GetComponent<CTextRenderer>()->SetText(wstring(tempGas.begin(), tempGas.end()));
			m_pSupplyText->GetComponent<CTextRenderer>()->SetText(wstring(tempSupply.begin(), tempSupply.end()));
		}
	}



	if (GETKEYDOWN(VK_F9))
	{
		m_iMineral += 10000;
		m_iVespeneGas += 10000;
	}
}

void CPlayer::LoadComponent(FILE * pFile)
{
}

void CPlayer::SaveComponent(FILE * pFile)
{
}

CComponent * CPlayer::clone()
{
	return nullptr;
}

CPlayer::CPlayer(const CPlayer & component) :
	m_eTeamColor(TC_RED),
	m_eRaceType(RT_RANDOM),
	m_iMineral(50),
	m_iVespeneGas(0),
	m_iMaxPopulation(0),
	m_iCurrentPopulation(0)
{
	memset(m_pUpgradeState, 0, sizeof(unsigned int) * (int)UT_END);
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_PLAYER;
}

CPlayer::CPlayer():
	m_eTeamColor(TC_RED),
	 m_eRaceType(RT_RANDOM),
	 m_iMineral(50),
	 m_iVespeneGas(0),
	 m_iMaxPopulation(0),
	 m_iCurrentPopulation(0)
{
	memset(m_pUpgradeState, 0, sizeof(unsigned int) * (int)UT_END);	
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_PLAYER;
}


CPlayer::~CPlayer()
{
}
