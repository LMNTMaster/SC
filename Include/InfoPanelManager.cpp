#include "InfoPanelManager.h"
#include "GameObject.h"
#include "Component.h"
#include "Components\Transform.h"
#include "Components\UnitInfo.h"
#include "Components\UIRenderer.h"
#include "Components\ButtonCollider.h"
#include "Components\Player.h"
#include "ResourceManager.h"
#include "Layer.h"
#include "Components\InfoPanelButton.h"
#include "Components\TextRenderer.h"
#include "Components\UnitStatus.h"
#include "Components\ProgressBar.h"
#include "Texture.h"


CInfoPanelManager* CInfoPanelManager::m_pInstance = NULL;

void CInfoPanelManager::ClearInfoPanel()
{
	list<CGameObject*>::iterator	iter;
	list<CGameObject*>::iterator iterEnd = m_CurrentContainedObjectList.end();
	
	for (iter = m_CurrentContainedObjectList.begin(); iter != iterEnd; ++iter)
	{		
		if ((*iter)->GetComponent<CButtonCollider>())
		{
			(*iter)->GetComponent<CButtonCollider>()->SetEnable(false);
		}
		(*iter)->SetDestroy(true);	
	}
	
	m_CurrentContainedObjectList.clear();
}

void CInfoPanelManager::UpdateInfoPanel(list<class CGameObject*> selectedUnitsList)
{
	list<CGameObject*>::iterator	 iter;
	list<CGameObject*>::iterator iterEnd = selectedUnitsList.end();


	ClearInfoPanel();

	int i = 0;
	for (iter = selectedUnitsList.begin(); iter != iterEnd; ++iter)
	{
		CGameObject* pButtonObject = new CGameObject("InfoUnitButton");
		m_pInfoPanelLayer->AddGameObject(pButtonObject);
		pButtonObject->GetTransform()->SetPosition(425 + ((i % 6) * 55), 625 + ((int)(i / 6) * 55));
		CUIRenderer* pBackRenderer = pButtonObject->AddComponent<CUIRenderer>();
		CUIRenderer* pRenderer = pButtonObject->AddComponent<CUIRenderer>();
		CButtonCollider* pCollider = pButtonObject->AddComponent<CButtonCollider>();
		CInfoPanelButton* pButtonEvent = pButtonObject->AddComponent<CInfoPanelButton>();
		pButtonEvent->SetUnit(*iter);
		pBackRenderer->SetSize(50, 50);
		pRenderer->SetSize(40, 40);
		pButtonObject->GetTransform()->SetPivot(CVector2(0.5f, 0.5f));
		if (!(*iter)->GetComponent<CUnitInfo>() || !(*iter)->GetComponent<CUnitInfo>()->GetUnitButtonTexture())
		{
			assert(0);
		}
		pRenderer->SetTexture((*iter)->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		pCollider->SetSize(50, 50);

		RACE_TYPE eType = (*iter)->GetPilot()->GetRaceType();
		switch (eType)
		{
		case RT_TERRAN:
		{
			pBackRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Terran_Background"));
		}
		break;
		case RT_PROTOSS:
		{
			pBackRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Protoss_Background"));
		}
		break;
		case RT_ZERG:
		{
			pBackRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Zerg_Background"));
		}
		break;
		default:
			break;
		}

		m_CurrentContainedObjectList.push_back(pButtonObject);
		++i;
	}
}

void CInfoPanelManager::UpdateInfoPanel(CUnitInfo * pInfo)
{		
	
	ClearInfoPanel();
	if (!pInfo)
		return;

	CPlayer* pPlayer = pInfo->GameObject()->GetScene()->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	CUnitStatus* pStatus = pInfo->GameObject()->GetComponent<CUnitStatus>();

	CGameObject* pName = new CGameObject("InfoUnitName");
	m_pInfoPanelLayer->AddGameObject(pName);
	CTextRenderer* pText = pName->AddComponent<CTextRenderer>();
	pText->SetAlign(TA_CENTER);
	pText->SetColor(184, 184, 232);
	pText->SetTextSize(15);
	string name = pInfo->GameObject()->GetName();
	pText->SetText(wstring(name.begin(), name.end()));
	pText->SetPosition(650,580);


	m_CurrentContainedObjectList.push_back(pName);
	
	if (pInfo->m_eInfoState == IS_BUILD)
	{
		CGameObject* pCondition = new CGameObject("InfoCondition");
		m_pInfoPanelLayer->AddGameObject(pCondition);
		CTextRenderer* pConditionText = pCondition->AddComponent<CTextRenderer>();
		pConditionText->SetAlign(TA_CENTER);
		pConditionText->SetColor(184, 184, 232);
		pConditionText->SetTextSize(15);
		wstring strCondition(L"Building");
		pConditionText->SetText(strCondition);
		pConditionText->SetPosition(650, 615);

		m_CurrentContainedObjectList.push_back(pCondition);
	}
	else if (pInfo->m_eInfoState == IS_UPGRADE)
	{
		CGameObject* pCondition = new CGameObject("InfoCondition");
		m_pInfoPanelLayer->AddGameObject(pCondition);
		CTextRenderer* pConditionText = pCondition->AddComponent<CTextRenderer>();
		pConditionText->SetAlign(TA_CENTER);
		pConditionText->SetColor(184, 184, 232);
		pConditionText->SetTextSize(15);
		wstring strCondition(L"Upgrade");
		pConditionText->SetText(strCondition);
		pConditionText->SetPosition(650, 615);

		m_CurrentContainedObjectList.push_back(pCondition);
	}	

	CGameObject* pHP = new CGameObject("InfoUnitHP");
	m_pInfoPanelLayer->AddGameObject(pHP);
	CTextRenderer* pHPText = pHP->AddComponent<CTextRenderer>();
	pHPText->SetTextSize(15);
	pHPText->SetColor(32, 200, 32);
	pHPText->SetPosition(435, 695);

	char value[128] = {};
	char maxValue[128] = {};
	itoa((int)pStatus->GetCurrentHP(), value, 10);
	itoa((int)pStatus->GetMaxHP(), maxValue, 10);

	string strValue = value + string(" / ") + maxValue;
	wstring wstrValue;
	wstrValue.assign(strValue.begin(), strValue.end());
	pHPText->SetText(wstrValue);

	m_CurrentContainedObjectList.push_back(pHP);


	if (pInfo->GameObject()->GetComponent<CUnitStatus>()->GetMaxMP() != 0)
	{
		CGameObject* pMP = new CGameObject("InfoUnitMP");
		m_pInfoPanelLayer->AddGameObject(pMP);
		CTextRenderer* pMPText = pMP->AddComponent<CTextRenderer>();
		pMPText->SetTextSize(15);
		pMPText->SetColor(32, 32, 200);
		pMPText->SetPosition(435, 710);

		char value[128] = {};
		char maxValue[128] = {};
		itoa((int)pStatus->GetCurrentMP(), value, 10);
		itoa((int)pStatus->GetMaxMP(), maxValue, 10);

		string strValue = value + string(" / ") + maxValue;
		wstring wstrValue;
		wstrValue.assign(strValue.begin(), strValue.end());
		pMPText->SetText(wstrValue);

		m_CurrentContainedObjectList.push_back(pMP);
	}
	if (pInfo->GameObject()->GetComponent<CUnitStatus>()->GetMaxShield() != 0)
	{
		CGameObject* pShield = new CGameObject("InfoUnitShield");
		m_pInfoPanelLayer->AddGameObject(pShield);
		CTextRenderer* pShieldText = pShield->AddComponent<CTextRenderer>();
		pShieldText->SetTextSize(15);
		pShieldText->SetColor(184, 184, 232);
		pShieldText->SetPosition(435, 680);


		char value[128] = {};
		char maxValue[128] = {};
		itoa((int)pStatus->GetCurrentShield(), value, 10);
		itoa((int)pStatus->GetMaxShield(), maxValue, 10);

		string strValue = value + string(" / ") + maxValue;
		wstring wstrValue;
		wstrValue.assign(strValue.begin(), strValue.end());
		pShieldText->SetText(wstrValue);

		m_CurrentContainedObjectList.push_back(pShield);
	}

	if (pInfo->m_eInfoState == IS_BUILD || pInfo->m_eInfoState == IS_UPGRADE)
	{
		CGameObject* pProgress = new CGameObject("InfoUnitProgress");
		m_pInfoPanelLayer->AddGameObject(pProgress);
		pProgress->GetTransform()->SetPosition(650, 645);
		CProgressBar* pProgressBar = pProgress->AddComponent<CProgressBar>();
		pProgressBar->SetSize(180, 15);
		pProgressBar->SetProgress(pInfo->m_fProgress);


		m_CurrentContainedObjectList.push_back(pProgress);

		CGameObject* pQueue[5] = {};


		list<CGameObject*>::iterator iter = pInfo->m_WorkList.begin();
		list<CGameObject*>::iterator iterEnd = pInfo->m_WorkList.end();
		list<CTexture*>::iterator textureIter = pInfo->m_WorkButtonTextureList.begin();
		list<CTexture*>::iterator textureIterEnd = pInfo->m_WorkButtonTextureList.end();

		pQueue[0] = new CGameObject("Queue");
		m_pInfoPanelLayer->AddGameObject(pQueue[0]);
		CUIRenderer* pUIBackgroundRenderer = pQueue[0]->AddComponent<CUIRenderer>();
		CUIRenderer* pUIForegroundRenderer = pQueue[0]->AddComponent<CUIRenderer>();
		pUIBackgroundRenderer->SetSize(54, 54);
		pUIForegroundRenderer->SetSize(35, 35);
		pQueue[0]->AddComponent<CButtonCollider>();

		switch (pPlayer->GetRaceType())
		{
			case RT_TERRAN:
			{
				pUIBackgroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Terran_Background"));
				pUIForegroundRenderer->SetTexture(pInfo->m_pWorkTargetButtonTexture);
			}
			break;
			case RT_PROTOSS:
			{
				pUIBackgroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Protoss_Background"));
				pUIForegroundRenderer->SetTexture(pInfo->m_pWorkTargetButtonTexture);
			}
			break;
			case RT_ZERG:
			{
				pUIBackgroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Zerg_Background"));
				pUIForegroundRenderer->SetTexture(pInfo->m_pWorkTargetButtonTexture);
			}
			break;
		default:
			break;
		}


		m_CurrentContainedObjectList.push_back(pQueue[0]);

		for (int i = 1; i < 5; ++i)
		{
			pQueue[i] = new CGameObject("Queue");

			m_pInfoPanelLayer->AddGameObject(pQueue[i]);
			CUIRenderer* pUIBackgroundRenderer = pQueue[i]->AddComponent<CUIRenderer>();
			CUIRenderer* pUIForegroundRenderer = pQueue[i]->AddComponent<CUIRenderer>();

			pUIBackgroundRenderer->SetSize(54, 54);
			pUIForegroundRenderer->SetSize(35, 35);

			pQueue[i]->AddComponent<CButtonCollider>();

			switch (pPlayer->GetRaceType())
			{
			case RT_TERRAN:
			{				
				pUIBackgroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Terran_Background"));				
				if (textureIter == textureIterEnd)
				{
					char cNum[4] = {};
					itoa((i + 1), cNum, 10);
					pUIForegroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Terran_Queue" + string(cNum)));
				}
				else
				{
					pUIForegroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture((*textureIter)->GetTextureKey()));
				}
			}
			break;
			case RT_PROTOSS:
			{
				pUIBackgroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Protoss_Background"));
				if (textureIter == textureIterEnd)
				{
					char cNum[4] = {};
					itoa((i + 1), cNum, 10);
					pUIForegroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Terran_Queue" + string(cNum)));
				}
				else
				{
					pUIForegroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture((*textureIter)->GetTextureKey()));
				}
			}
			break;
			case RT_ZERG:
			{
				pUIBackgroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Zerg_Background"));
				if (textureIter == textureIterEnd)
				{
					char cNum[4] = {};
					itoa((i + 1), cNum, 10);
					pUIForegroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Terran_Queue" + string(cNum)));
				}
				else
				{
					pUIForegroundRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture((*textureIter)->GetTextureKey()));
				}
			}
			break;
			default:
				break;
			}



			m_CurrentContainedObjectList.push_back(pQueue[i]);

			if(textureIter != textureIterEnd)
			++textureIter;

			if(iter != iterEnd)
			++iter;
		}

		

		CVector2 basePos = CVector2(530, 630);
		pQueue[0]->GetTransform()->SetPosition(basePos);
		pQueue[1]->GetTransform()->SetPosition(basePos + CVector2(0,60));
		pQueue[2]->GetTransform()->SetPosition(basePos + CVector2(60,60));
		pQueue[3]->GetTransform()->SetPosition(basePos + CVector2(120, 60));
		pQueue[4]->GetTransform()->SetPosition(basePos + CVector2(180, 60));


		
	}
	else
	{

	}
}

void CInfoPanelManager::Initialize()
{
}

CInfoPanelManager::CInfoPanelManager()
{
}


CInfoPanelManager::~CInfoPanelManager()
{
}
