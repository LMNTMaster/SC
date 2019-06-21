#include "ConsoleButtonManager.h"
#include "GameObject.h"
#include "ConsoleButton.h"
#include "Component.h"
#include "Components\ControlButton.h"

CConsoleButtonManager* CConsoleButtonManager::m_pInstance = NULL;

void CConsoleButtonManager::UpdateControlPanel(CGameObject * pGameObject)
{	
	if (pGameObject)
	{
		ClearControlPanel();
	
		m_pTargetObject = pGameObject;
		list<class CConsoleButton*> tempList = pGameObject->GetButtonList();
		list<class CConsoleButton*>::const_iterator iter;
		list<class CConsoleButton*>::const_iterator iterEnd = tempList.end();
		for (iter = tempList.begin(); iter != iterEnd; ++iter)
		{
			CConsoleButton* pTargetButton = (*iter);
			m_vecControlPanelButton[(*iter)->GetPanelIndex()]->GetComponent<CControlButton>()->SetConsoleButton(pTargetButton);
		}
	}	
	else
	{
		ClearControlPanel();
	}
}

void CConsoleButtonManager::ClearControlPanel()
{
	for (int i = 0; i < m_vecControlPanelButton.size(); ++i)
	{
		m_vecControlPanelButton[i] ->GetComponent<CControlButton>()->m_pButton = NULL;
	}
}

void CConsoleButtonManager::Initialize()
{
	m_vecControlPanelButton.resize(9);
}

CConsoleButtonManager::CConsoleButtonManager():
	m_pTargetObject(NULL)
{
}


CConsoleButtonManager::~CConsoleButtonManager()
{
}
