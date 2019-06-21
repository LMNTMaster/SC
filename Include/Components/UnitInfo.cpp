#include "UnitInfo.h"
#include "../Texture.h"
#include "../ResourceManager.h"
#include "../Timer.h"
#include "UnitStatus.h"
#include "Player.h"
#include "../Scene.h"
#include "../Layer.h"

#include "../GameObject.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "../Scene.h"
#include "../Layer.h"
#include "../SceneManager.h"
#include "../FileStream.h"
#include "../Tile.h"

CVector2 CUnitInfo::GetAvailablePosition()
{
	CVector2 origin = m_pTransform->GetPosition();
	CVector2 size = m_pGameObject->GetComponent<CSpriteRenderer>()->GetSize();
	origin.x -= size.x * m_pTransform->GetPivot().x;
	origin.y -= size.y * m_pTransform->GetPivot().y;

	CVector2 spawnPosition = origin + CVector2(0, size.y);

	int iStructureWidth = m_pGameObject->GetComponent<CStructure>()->GetSize().x;
	int iStructureHeight = m_pGameObject->GetComponent<CStructure>()->GetSize().y;

	int iX = (int)spawnPosition.x / 32;
	int iY = (int)spawnPosition.y / 32;
	int index = iY * m_pGameObject->GetScene()->GetGridSize().x + iX;

	//BFS

	return origin + CVector2(0,size.y);
}

void CUnitInfo::AddQueue(CGameObject * pTarget, CTexture * pButtonTexture)
{
	if (m_WorkList.size() < 4)
	{
		CPlayer* pPlayer = m_pGameObject->GetScene()->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

		if (pPlayer->GetMineral() >= pTarget->GetComponent<CUnitStatus>()->m_fMineralRequirement &&
			pPlayer->GetVespeneGas() >= pTarget->GetComponent<CUnitStatus>()->m_fGasRequirement &&
			pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() >= pTarget->GetComponent<CUnitStatus>()->m_fPopulationRequirement)
		{
			pPlayer->AddCurrentPopulation(pTarget->GetComponent<CUnitStatus>()->m_fPopulationRequirement);
			pPlayer->AddMineral(-pTarget->GetComponent<CUnitStatus>()->m_fMineralRequirement);
			pPlayer->AddVespeneGas(-pTarget->GetComponent<CUnitStatus>()->m_fGasRequirement);
			m_WorkList.push_back(pTarget);
			m_WorkButtonTextureList.push_back(pButtonTexture);
		}
	}
}

void CUnitInfo::Start()
{
}

void CUnitInfo::Update()
{
	float deltaTime = GET_SINGLE(CTimer)->GetDeltaTime();


	if (!m_pWorkTarget)
	{
		if (!m_WorkList.empty())
		{
			m_pWorkTarget = m_WorkList.front();
			m_WorkList.erase(m_WorkList.begin());
			m_pWorkTargetButtonTexture = m_WorkButtonTextureList.front();
			m_WorkButtonTextureList.erase(m_WorkButtonTextureList.begin());
			m_fProgress = 0;
		}
		else 
		{
			m_eInfoState = IS_NONE;
		}
	}
	else
	{
		if (m_pWorkTarget->GetComponent<CUnitStatus>())
		{
			m_eInfoState = IS_BUILD;
		}
		else
		{
			//업그레이드의 경우 work target이 CunitStatus를 가지고 있지 않아야 함.
			m_eInfoState = IS_UPGRADE;
		}		
		m_fProgressTimer += deltaTime;
		float fCreateTime = m_pWorkTarget->GetComponent<CUnitStatus>()->GetCreateTime();
		if (m_fProgressTimer >= fCreateTime)
		{
			CGameObject* pCreatedObject = m_pWorkTarget->clone();
			pCreatedObject->SetPilot(m_pGameObject->GetPilot());
			pCreatedObject->SetSelected(false);
			pCreatedObject->SetToAirUnit(false);

			pCreatedObject->GetTransform()->SetPosition(GetAvailablePosition());
			if(!pCreatedObject->IsAirUnit())
			{
				GET_SINGLE(CSceneManager)->GetCurrentScene()->GetLayer("GroundUnit")->AddGameObject(pCreatedObject);
			}


			m_pWorkTarget = NULL;
			m_fProgressTimer = 0;
		}
		else
		{
			m_fProgress = m_fProgressTimer / fCreateTime;
		}
	}
	
}

void CUnitInfo::SaveComponent(FILE * pFile)
{
	bool containTexture ;
	if (m_pUnitButtonTexture)
	{
		containTexture = true;
	}
	else
	{
		containTexture = false;
	}

	fwrite(&containTexture, 1, 1, pFile);


	if (containTexture)
	{
	
		char strTextureKey[128] = {};	
		strcpy(strTextureKey, m_pUnitButtonTexture->GetTextureKey().c_str());
		int iLength = 0;
		iLength = strlen(strTextureKey);

		fwrite(&iLength, 4, 1, pFile);
		fwrite(&strTextureKey, 1, iLength, pFile);
	}
}

void CUnitInfo::LoadComponent(FILE * pFile)
{
	bool containTexture = false;
	fread(&containTexture, 1, 1, pFile);

	if (containTexture)
	{
		char strTextureKey[128] = {};
		int iLength = 0;
		fread(&iLength, 4, 1, pFile);
		fread(&strTextureKey, 1, iLength, pFile);

		m_pUnitButtonTexture = GET_SINGLE(CResourceManager)->FindTexture(string(strTextureKey));
	}

}

CComponent * CUnitInfo::clone()
{
	return new CUnitInfo(*this);
}

CUnitInfo::CUnitInfo(const CUnitInfo & component) :
	m_eInfoState(IS_NONE),
	m_pWorkTarget(NULL),
	m_fProgress(0),
	m_pWireframeTexture(NULL),
	m_pAttack(NULL),
	m_pDeffence(NULL),
	m_pShield(NULL),
	m_pUnitButtonTexture(NULL),
	m_fProgressTimer(0)
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_UNITINFO;
	//DO NOTHING

	m_pUnitButtonTexture = component.m_pUnitButtonTexture;
	m_WorkList.clear();
	m_WorkButtonTextureList.clear();
	m_pWorkTargetButtonTexture = NULL;
	m_pWorkTarget = NULL;


}

CUnitInfo::CUnitInfo():
	m_eInfoState(IS_NONE),
	m_pWorkTarget(NULL),
	m_fProgress(0),
	m_pWireframeTexture(NULL),
	m_pAttack(NULL),
	m_pDeffence(NULL),
	m_pShield(NULL),
	m_pUnitButtonTexture(NULL),
	m_fProgressTimer(0)
{

	m_WorkList.clear();
	m_WorkButtonTextureList.clear();
	m_pWorkTargetButtonTexture = NULL;
	m_pWorkTarget = NULL;

	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_UNITINFO;
}


CUnitInfo::~CUnitInfo()
{
}
