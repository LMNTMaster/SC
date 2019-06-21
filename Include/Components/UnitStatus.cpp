#include "UnitStatus.h"
#include "../GameObject.h"
#include "../Component.h"
#include "SpriteRenderer.h"
#include "../Sprite.h"
#include "../ResourceManager.h"
#include "Transform.h"
#include "../Timer.h"
#include "../Texture.h"
#include "../Layer.h"
#include "Attack.h"
#include "../Tile.h"
#include "Player.h"
#include "../FogOfWarManager.h"

void CUnitStatus::SetSightTile()
{
	CScene* pScene = m_pGameObject->GetScene();
	CVector2 position = m_pTransform->GetPosition();
	CVector2 gridSize = pScene->GetGridSize();

	int iX = position.x / 32;
	int iY = position.y / 32;
	int idx = iY * gridSize.x + iX;	

	int maxLevel = m_fSightRadius ;


	for (int y = -maxLevel; y <= maxLevel; ++y)
	{
		for (int x = -maxLevel; x <= maxLevel; ++x)
		{
			//타일 범위 밖이면 연산하지 않음
			if (iX + x < 0 || iX + x > gridSize.x || iY + y < 0 || iY + y > gridSize.y)
			{
				continue;
			}

			//타일의 중심부터 유닛과의 거리가 충돌 범위 내에 있으면 추가함.
			int iTileIndex = idx + y * gridSize.x + x;

			CTile* pTile = pScene->GetTileByIndex(iTileIndex);
			CVector2 temp = pTile->GetWorldPosition() + CVector2(16, 16);
			temp -= position;
			float distance = temp.length();
			if (distance <= m_fSightRadius * 32 + 16)
			{
				GET_SINGLE(CFogOfWarManager)->SetTileState(iTileIndex, FS_VISIBLE, true);
			}
		}
	}
}

void CUnitStatus::Start()
{
}

void CUnitStatus::Update()
{
	SetSightTile();

	m_fHPGenTime += GET_SINGLE(CTimer)->GetDeltaTime();
	m_fMPGenTime += GET_SINGLE(CTimer)->GetDeltaTime();
	m_fShieldGenTime += GET_SINGLE(CTimer)->GetDeltaTime();
	

	if (m_fHPGenTime >= m_fHPGeneration)
	{
		m_fHPGenTime -= m_fHPGeneration;
		m_fHP += m_fHPGenerationAmount;
		if (m_fHP >= m_fHPMax)
		{
			m_fHP = m_fHPMax;
		}
	}
	if (m_fMPGenTime >= m_fMPGeneration)
	{
		m_fMPGenTime -= m_fMPGeneration;
		m_fMP += m_fMPGenerationAmount;
		if (m_fMP >= m_fMPMax)
		{
			m_fMP = m_fMPMax;
		}
	}
	if (m_fShieldGenTime >= m_fShieldGeneration)
	{
		m_fShieldGenTime -= m_fShieldGeneration;
		m_fShield += m_fShieldGenerationAmount;
		if (m_fShield >= m_fShieldMax)
		{
			m_fShield = m_fShieldMax;
		}
	}
		
	if (m_fHP <= 0)
	{
		CSprite* pDeathSprite = m_pGameObject->GetComponent<CSpriteRenderer>()->FindSprite(m_pGameObject->GetName() + "Death");		

		//더미 유닛 생성
		CGameObject* pDeath = new CGameObject("Dummy");
		m_pGameObject->GetLayer()->AddGameObject(pDeath);
		pDeath->GetTransform()->SetPosition(m_pTransform->GetPosition());
		CSpriteRenderer* pRenderer = pDeath->AddComponent<CSpriteRenderer>();		
		pRenderer->AddSprite(m_pGameObject->GetName() + "Death", pDeathSprite);
		pRenderer->ChangeCurrentClip(m_pGameObject->GetName() + "Death");
		CVector2 size = pRenderer->GetCurrentClip()->GetCellSize();
		pRenderer->SetSize(size);
		vector<unsigned int> builtTileIndex;

		if (m_pGameObject->GetComponent<CStructure>())
		{
			builtTileIndex = m_pGameObject->GetComponent<CStructure>()->GetBuiltTileIndex();
			
			for (int i = 0; i < builtTileIndex.size(); ++i)
			{
				m_pGameObject->GetScene()->GetTileByIndex(builtTileIndex[i])->SetMovable(true);
				m_pGameObject->GetScene()->GetTileByIndex(builtTileIndex[i])->SetBuildable(true);
			}	
		}

		m_pGameObject->SetDestroy(true);

		//list<CGameObject*>::iterator iter;
		//list<CGameObject*>::iterator iterEnd = m_AttackingUnitList.end();
		//for (iter = m_AttackingUnitList.begin(); iter != iterEnd; ++iter)
		//{
		//	(*iter)->GetComponent<CAttack>()->SetTarget(NULL);
		//}
	}
}

void CUnitStatus::LoadComponent(FILE * pFile)
{
	fread(&m_fCreateTime, 4, 1, pFile);
	fread(&m_fMineralRequirement, 4, 1, pFile);
	fread(&m_fGasRequirement, 4, 1, pFile);
	fread(&m_fPopulationRequirement, 4, 1, pFile);

	fread(&m_fHPMax, 4, 1, pFile);
	fread(&m_fHP, 4, 1, pFile);
	fread(&m_fHPGeneration, 4, 1, pFile);
	fread(&m_fHPGenerationAmount, 4, 1, pFile);
	fread(&m_fHPGenTime, 4, 1, pFile);

	fread(&m_fMPMax, 4, 1, pFile);
	fread(&m_fMP, 4, 1, pFile);
	fread(&m_fMPGeneration, 4, 1, pFile);
	fread(&m_fMPGenerationAmount, 4, 1, pFile);
	fread(&m_fMPGenTime, 4, 1, pFile);

	fread(&m_fShieldMax, 4, 1, pFile);
	fread(&m_fShield, 4, 1, pFile);
	fread(&m_fShieldGeneration, 4, 1, pFile);
	fread(&m_fShieldGenerationAmount, 4, 1, pFile);
	fread(&m_fShieldGenTime, 4, 1, pFile);

	fread(&m_fSightRadius, 4, 1, pFile);
}

void CUnitStatus::SaveComponent(FILE * pFile)
{
	fwrite(&m_fCreateTime, 4, 1, pFile);
	fwrite(&m_fMineralRequirement, 4, 1, pFile);
	fwrite(&m_fGasRequirement, 4, 1, pFile);
	fwrite(&m_fPopulationRequirement, 4, 1, pFile);

	fwrite(&m_fHPMax, 4, 1, pFile);
	fwrite(&m_fHP, 4, 1, pFile);
	fwrite(&m_fHPGeneration, 4, 1, pFile);
	fwrite(&m_fHPGenerationAmount, 4, 1, pFile);
	fwrite(&m_fHPGenTime, 4, 1, pFile);

	fwrite(&m_fMPMax, 4, 1, pFile);
	fwrite(&m_fMP, 4, 1, pFile);
	fwrite(&m_fMPGeneration, 4, 1, pFile);
	fwrite(&m_fMPGenerationAmount, 4, 1, pFile);
	fwrite(&m_fMPGenTime, 4, 1, pFile);

	fwrite(&m_fShieldMax, 4, 1, pFile);
	fwrite(&m_fShield, 4, 1, pFile);
	fwrite(&m_fShieldGeneration, 4, 1, pFile);
	fwrite(&m_fShieldGenerationAmount, 4, 1, pFile);
	fwrite(&m_fShieldGenTime, 4, 1, pFile);

	fwrite(&m_fSightRadius, 4, 1, pFile);
}

CComponent * CUnitStatus::clone()
{
	return new CUnitStatus(*this);
}

CUnitStatus::CUnitStatus(const CUnitStatus & component) :
	m_fHPMax(0),
	m_fMPMax(0),
	m_fShield(0),
	m_fHPGeneration(0),
	m_fMPGeneration(1),
	m_fShieldGeneration(1),
	m_fHPGenerationAmount(0),
	m_fMPGenerationAmount(1),
	m_fShieldGenerationAmount(1),
	m_fSightRadius(5),
	m_fHPGenTime(0),
	m_fMPGenTime(0),
	m_fShieldGenTime(0),
	m_fCreateTime(10),
	m_fMineralRequirement(0),
	m_fGasRequirement(0)
{
	m_fCreateTime	=   component.m_fCreateTime;
	m_fMineralRequirement	=    component.m_fMineralRequirement;
	m_fGasRequirement	=   component.m_fGasRequirement;
	m_fPopulationRequirement	=    component.m_fPopulationRequirement;

	m_fHPMax	=    component.m_fHPMax;
	m_fHP	=   component.m_fHP;
	m_fHPGeneration	=    component.m_fHPGeneration;
	m_fHPGenerationAmount	=   component.m_fHPGenerationAmount;
	m_fHPGenTime	=    component.m_fHPGenTime;

	m_fMPMax	=    component.m_fMPMax;
	m_fMP	=    component.m_fMP;
	m_fMPGeneration	=    component.m_fMPGeneration;
	m_fMPGenerationAmount	=    component.m_fMPGenerationAmount;
	m_fMPGenTime	=    component.m_fMPGenTime;

	m_fShieldMax	=    component.m_fShieldMax;
	m_fShield	=    component.m_fShield;
	m_fShieldGeneration	=    component.m_fShieldGeneration;
	m_fShieldGenerationAmount	=    component.m_fShieldGenerationAmount;
	m_fShieldGenTime	=    component.m_fShieldGenTime;

	m_fSightRadius	=    component.m_fSightRadius;


	SetHPMaxCondition();
	SetMPMaxCondition();
	SetShieldMaxCondition();

	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_UNIT_STATUS;
}

CUnitStatus::CUnitStatus() :
	m_fHPMax(0),
	m_fMPMax(0),
	m_fShield(0),
	m_fHPGeneration(0),
	m_fMPGeneration(1),
	m_fShieldGeneration(1),
	m_fHPGenerationAmount(0),
	m_fMPGenerationAmount(1),
	m_fShieldGenerationAmount(1),
	m_fSightRadius(5),
	m_fHPGenTime(0),
	m_fMPGenTime(0),
	m_fShieldGenTime(0),
	m_fCreateTime(10),
	m_fMineralRequirement(0),
	m_fGasRequirement(0)
{
	SetHPMaxCondition();
	SetMPMaxCondition();
	SetShieldMaxCondition();

	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_UNIT_STATUS;
}


CUnitStatus::~CUnitStatus()
{
}
