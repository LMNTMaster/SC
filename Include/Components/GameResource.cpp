#include "GameResource.h"
#include "../Timer.h"
#include "../GameObject.h"
#include "Gather.h"
#include "../ResourceManager.h"
#include "../SceneManager.h"
#include "../Scene.h"
#include "../Layer.h"
#include "SpriteRenderer.h"
#include "Animator\GasBox.h"
#include "Animator\GasSac.h"
#include "Animator\GasTank.h"
#include "Animator\MineralOrb.h"
#include "Stop.h"

CGameObject * CResource::ReturnUnitFromQueue()
{
	CGameObject* temp = m_qGatheringUnit.front();
	m_qGatheringUnit.pop();

	CGather* pGather = temp->GetComponent<CGather>();
	if (pGather)
	{
		if (pGather->GetNearestBase())
		{
			pGather->RequestReturnToBasement();
		}
		else
		{
			pGather->GameObject()->GetComponent<CStop>();
		}
	}
	return temp;
}

void CResource::Update()
{
	if (!m_qGatheringUnit.empty())
	{
		m_fCurrentTime += GET_SINGLE(CTimer)->GetDeltaTime();

		if (m_fCurrentTime >= m_fR2BTime)
		{
			m_fCurrentTime -= m_fR2BTime;
			CGameObject* pReturnUnit = ReturnUnitFromQueue();
			m_iValue -= pReturnUnit->GetComponent<CGather>()->GetGatherAmount();
			if (m_eType == RT_MINERAL)
			{
				CGameObject* pOrb = GET_SINGLE(CResourceManager)->FindUnit("MineralOrb")->clone();
				GET_SINGLE(CSceneManager)->GetCurrentScene()->GetLayer("GroundUnit")->AddGameObject(pOrb);
				pOrb->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("MineralOrb0");
				pOrb->GetComponent<CMineralOrb>()->SetTarget(pReturnUnit);
				pReturnUnit->GetComponent<CGather>()->SetOrb(pOrb);
			}
			else if (m_eType == RT_VESPENE_GAS)
			{
				if (pReturnUnit->GetName().find("SCV") != string::npos)
				{
					CGameObject* pOrb = GET_SINGLE(CResourceManager)->FindUnit("GasTank")->clone();
					GET_SINGLE(CSceneManager)->GetCurrentScene()->GetLayer("GroundUnit")->AddGameObject(pOrb);
					pOrb->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("GasTank");
					pOrb->GetComponent<CGasTank>()->SetTarget(pReturnUnit);
					pReturnUnit->GetComponent<CGather>()->SetOrb(pOrb);
				}
				else if(pReturnUnit->GetName().find("Probe") != string::npos)
				{
					CGameObject* pOrb = GET_SINGLE(CResourceManager)->FindUnit("GasBox")->clone();
					GET_SINGLE(CSceneManager)->GetCurrentScene()->GetLayer("GroundUnit")->AddGameObject(pOrb);
					pOrb->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("GasBox0");
					pOrb->GetComponent<CGasBox>()->SetTarget(pReturnUnit);
					pReturnUnit->GetComponent<CGather>()->SetOrb(pOrb);
				}
				else if (pReturnUnit->GetName().find("Drone") != string::npos)
				{
					CGameObject* pOrb = GET_SINGLE(CResourceManager)->FindUnit("GasSac")->clone();
					GET_SINGLE(CSceneManager)->GetCurrentScene()->GetLayer("GroundUnitLayer")->AddGameObject(pOrb);
					pOrb->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("GasSac0");
					pOrb->GetComponent<CGasSac>()->SetTarget(pReturnUnit);
					pReturnUnit->GetComponent<CGather>()->SetOrb(pOrb);
				}
			}

			pReturnUnit->GetComponent<CGather>()->SetGatherState(GS_RETURNTOBASEMENT);
		}
	}
}

void CResource::LoadComponent(FILE* pFile)
{
	fread(&m_eType, 4, 1, pFile);
	fread(&m_iValue, 4, 1, pFile);
}

void CResource::SaveComponent(FILE* pFile)
{
	fwrite(&m_eType, 4, 1, pFile);
	fwrite(&m_iValue, 4, 1, pFile);
}

CComponent * CResource::clone()
{
	return new CResource(*this);
}

CResource::CResource(const CResource & component)
{	
	m_eType = component.m_eType;
	m_iValue = component.m_iValue;
	m_fR2BTime = component.m_fR2BTime;
	m_fCurrentTime = 0;
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_RESOURCE;
}

CResource::CResource():
	m_eType(RT_MINERAL),
	m_iValue(2500),
	m_fR2BTime(5),
	m_fCurrentTime(0)
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_RESOURCE;
}


CResource::~CResource()
{
}
