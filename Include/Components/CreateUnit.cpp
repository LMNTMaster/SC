#include "CreateUnit.h"
#include "../GameObject.h"
#include "Transform.h"
#include "../ConsoleButton.h"
#include "../ResourceManager.h"
#include "UnitInfo.h"

void CCreateUnit::RequestCreateUnit(CTexture* pIconTexture)
{	
	m_pGameObject->GetComponent<CUnitInfo>()->AddQueue(m_pCreateTarget, pIconTexture);	
}

void CCreateUnit::Start()
{
	if (m_pCreateTarget)
	{
		if (m_pCreateTarget->GetName() == "SCV")
		{
			m_pButton = new CConsoleButton;
			m_pGameObject->AddButton(m_pButton);
			m_pButton->SetButtonName("SCV");
			m_pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranSCV_Pressed"));
			m_pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranSCV_Normal"));
			m_pButton->SetRequireCursor(false);
			m_pButton->SetRequireBuildMode(false);
			m_pButton->SetPanelIndex(0);
			m_pButton->SetShortcutKey('S');
			m_pButton->SetButtonComponent(this);
			m_pButton->SetExistNextPage(false);
			m_pButton->SetAdvanced(false);

			auto func = [&](CVector2, CGameObject*)
			{
				RequestCreateUnit(m_pButton->GetUpIconTexture());
			};
			m_pButton->SetFunction(func);
		}
	}
}

void CCreateUnit::SaveComponent(FILE * pFile)
{
}

void CCreateUnit::LoadComponent(FILE * pFile)
{
}

CComponent * CCreateUnit::clone()
{
	return nullptr;
}

CCreateUnit::CCreateUnit(const CCreateUnit & component)
{
}

CCreateUnit::CCreateUnit()
{
}


CCreateUnit::~CCreateUnit()
{
	if (m_pButton)
		delete m_pButton;
}
